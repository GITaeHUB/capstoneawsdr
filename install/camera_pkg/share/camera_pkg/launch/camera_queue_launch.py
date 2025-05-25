import launch
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('camera_index', default_value='0', description='Camera index for /dev/video0'),
        
        # 카메라 노드 실행
        Node(
            package='camera_pkg',
            executable='camera_node',
            name='camera_node',
            output='screen',
        ),
        
        # 차선 감지 노드 실행
        Node(
            package='camera_pkg',  # camera_pkg 내에 존재하는 노드
            executable='lane_detection_node_queue',
            name='lane_detection_node',
            output='screen'
        ),
    ])
