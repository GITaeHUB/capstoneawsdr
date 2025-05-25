#!/bin/bash

source ~/capstone_ws/install/setup.bash

echo "🟢 Starting motor test loop..."


echo "▶️ [${i}] Move forward"
ros2 topic pub --once /servo_cmd motor_control/msg/ServoCtrlMsg "{angle: 0.0, throttle: 60.0}"
sleep 2

echo "🔁 [${i}] Turn right"
ros2 topic pub --once /servo_cmd motor_control/msg/ServoCtrlMsg "{angle: 20.0, throttle: -60.0}"
sleep 2

echo "🔁 [${i}] Turn left"
ros2 topic pub --once /servo_cmd motor_control/msg/ServoCtrlMsg "{angle: -15.0, throttle: 65.0}"
sleep 2


echo "🛑 Stopping the vehicle"
ros2 topic pub --once /servo_cmd motor_control/msg/ServoCtrlMsg "{angle: 0.0, throttle: 0.0}"
