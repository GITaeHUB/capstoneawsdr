#include "servo_mux_pkg/servo_mux_node.hpp"
#include <cmath>

using motor_control::msg::ServoCtrlMsg;
using rplidar_ros::msg::ObjectInfoArray;
using namespace std::chrono_literals;

/* ---------- ctor ------------------------------------------------ */
ServoMuxNode::ServoMuxNode()
: Node("servo_mux"),
  avoid_time_(0, 0),
  recover_time_(0, 0)
{
  // 파라미터 선언
  trigger_dist_   = this->declare_parameter<double>("trigger_dist",    0.08);
  steer_mag_      = this->declare_parameter<double>("steer_magnitude", 1.0);
  avoid_throttle_ = this->declare_parameter<double>("avoid_throttle",  0.5);

  avoid_time_ = rclcpp::Duration::from_seconds(
                  this->declare_parameter<double>("avoid_sec", 1.0));
  recover_time_ = rclcpp::Duration::from_seconds(
                    this->declare_parameter<double>("recover_sec", 0.5));

  // 퍼블리셔: 최종 제어 명령
  pub_ = this->create_publisher<ServoCtrlMsg>("/ctrl_pkg/servo_msg", 10);

  // 모델 주행 명령 구독
  sub_model_ = this->create_subscription<ServoCtrlMsg>(
    "/model_cmd", 10,
    std::bind(&ServoMuxNode::modelCb, this, std::placeholders::_1));

  // 장애물 정보 구독
  sub_obj_ = this->create_subscription<ObjectInfoArray>(
    "/obstacle_info", 10,
    std::bind(&ServoMuxNode::objectCb, this, std::placeholders::_1));

  // 50Hz 주기로 tick()
  this->create_wall_timer(20ms, std::bind(&ServoMuxNode::tick, this));
}

/* ---------- model command cache -------------------------------- */
void ServoMuxNode::modelCb(const ServoCtrlMsg::SharedPtr msg)
{
  last_model_ = *msg;
}

/* ---------- obstacle processing -------------------------------- */
void ServoMuxNode::objectCb(const ObjectInfoArray::SharedPtr msg)
{
  if (state_ != State::IDLE) return;

  float min_d = trigger_dist_;
  float side = 0.0;

  for (const auto& o : msg->objects) {
    float x = -o.x;
    float y = -o.y;
    if (x <= 0.0 || std::abs(y) > 0.15) continue;
    float d = std::hypot(x, y);
    if (d < min_d) {
      min_d = d;
      side = y;
    }
  }

  if (min_d < trigger_dist_) {
    avoid_dir_ = (side >= 0.0) ? +1.0 : -1.0;
    state_ = State::AVOID;
    state_enter_time_ = this->now();
    RCLCPP_INFO(this->get_logger(),
      "[AVOID TRIGGER] Obstacle %.2f m (%+.2f y) → dir=%+.0f",
      min_d, side, avoid_dir_);
  }
}

/* ---------- tick: main control loop ---------------------------- */
void ServoMuxNode::tick()
{
  ServoCtrlMsg cmd;

  switch (state_) {
    case State::IDLE:
      cmd = last_model_;
      break;

    case State::AVOID: {
      double dt = (this->now() - state_enter_time_).seconds();
      RCLCPP_INFO(this->get_logger(), "[AVOID] active: %.2fs", dt);
      cmd.angle = steer_mag_ * avoid_dir_;
      cmd.throttle = avoid_throttle_;
      if (dt >= avoid_time_.seconds()) {
        state_ = State::RECOVER;
        state_enter_time_ = this->now();
      }
      break;
    }

    case State::RECOVER: {
      double dt = (this->now() - state_enter_time_).seconds();
      RCLCPP_INFO(this->get_logger(), "[RECOVER] active: %.2fs", dt);
      cmd.angle = 0.0;
      cmd.throttle = avoid_throttle_;
      if (dt >= recover_time_.seconds()) {
        state_ = State::IDLE;
      }
      break;
    }
  }

  pub_->publish(cmd);
}

/* ---------- main ----------------------------------------------- */
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ServoMuxNode>());
  rclcpp::shutdown();
  return 0;
}
