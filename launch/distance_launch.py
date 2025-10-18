from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    publisher_node = Node(
        package='distance_pkg',
        executable='distance_nodes',
        name='distance_publisher'
    )
    subscriber_node = Node(
        package='distance_pkg',
        executable='distance_nodes',
        name='distance_subscriber'
    )

    return LaunchDescription([
        publisher_node,
        subscriber_node
    ])
