#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='invert_laser',
            executable='invert_laser_node',
            name='invert_laser',
            parameters=[{'out_frame': 'lidar_back_v1_1'}]    #replace with your frame id
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='lidar2lidar_inv',
            parameters=[],
            remappings=[],
            arguments=['0.0', '0.0', '0.0', '0.0', '0.0', '3.14159', 'laser', 'lidar_front_v2_1']    #replace with your frame id
        )
    ])
