#pragma once
#include <rclcpp/rclcpp.hpp>
#include "motor_control/msg/servo_ctrl_msg.hpp"
#include "rplidar_ros/msg/object_info_array.hpp"

class ServoMuxNode : public rclcpp::Node
{
public:
  ServoMuxNode();

private:
  /* ----- internal state machine ----- */
  enum class State { IDLE, AVOID, RECOVER };
  State  state_{State::IDLE};
  rclcpp::Time state_enter_time_;

  /* ----- callbacks ----- */
  void modelCb(const motor_control::msg::ServoCtrlMsg::SharedPtr);
  void objectCb(const rplidar_ros::msg::ObjectInfoArray::SharedPtr);
  void tick();                                       // 50 Hz main loop

  /* ----- ROS I/O ----- */
  rclcpp::Publisher<motor_control::msg::ServoCtrlMsg>::SharedPtr         pub_;
  rclcpp::Subscription<motor_control::msg::ServoCtrlMsg>::SharedPtr      sub_model_;
  rclcpp::Subscription<rplidar_ros::msg::ObjectInfoArray>::SharedPtr     sub_obj_;

  motor_control::msg::ServoCtrlMsg last_model_;     // 최신 모델 명령

  /* ----- params ----- */
  double trigger_dist_;          // [m] 장애물 감지 거리 (0.08 m)
  double steer_mag_;             // ±1 조향 고정
  double avoid_throttle_;        // 회피/복귀 속도 (0.5)
  rclcpp::Duration avoid_time_;  // 1 s
  rclcpp::Duration recover_time_;// 0.5 s

  double avoid_dir_{1.0};        // +1 왼쪽, –1 오른쪽
};
