from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='deepracer_main',
            executable='deepracer_node',
            name='deepracer_node',
            output='screen',
            parameters=[{'servo_cmd_topic': '/servo_cmd'}]
        ),
    ])
