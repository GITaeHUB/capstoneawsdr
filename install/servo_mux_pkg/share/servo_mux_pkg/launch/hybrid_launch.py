from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    servo_mux = Node(
        package='servo_mux_pkg',
        executable='servo_mux_node',
        name='servo_mux',
        parameters=[
            {'trigger_dist': 0.08},
            {'steer_magnitude': 1.0},
            {'avoid_throttle': 0.5},
            {'avoid_sec': 1.0},
            {'recover_sec': 0.5}
        ],
        remappings=[
            ('/model_cmd', '/ctrl_pkg/servo_msg')  # 🔁 여기서 직접 매핑
        ]
    )
    return LaunchDescription([servo_mux])