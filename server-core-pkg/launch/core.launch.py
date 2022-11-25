import os
import yaml
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution
from ament_index_python.packages import get_package_share_directory
import xacro

def load_yaml(package_name, file_path):
    package_path = get_package_share_directory(package_name)
    absolute_file_path = os.path.join(package_path, file_path)

    try:
        with open(absolute_file_path, 'r') as file:
            return yaml.safe_load(file)
    except EnvironmentError:  # parent of IOError, OSError *and* WindowsError where available
        return None

def load_file(package_name, file_path):
    package_path = get_package_share_directory(package_name)
    absolute_file_path = os.path.join(package_path, file_path)
    try:
        with open(absolute_file_path, 'r') as file:
            return file.read()
    except EnvironmentError: # parent of IOError, OSError *and* WindowsError where available
        return None

def generate_launch_description():
    robot_description_config = xacro.process_file(
        os.path.join(
            get_package_share_directory("dobot_description"),
            "urdf",
            "dobot_moveit_desc.urdf.xacro",
        )
    )
    robot_description = {"robot_description": robot_description_config.toxml()}
    
    robot_description_semantic_config = load_file(
        "dobot_moveit_config", "config/dobot_palitra.srdf"
    )

    robot_description_semantic = {
        "robot_description_semantic": robot_description_semantic_config
    }

    kinematics_yaml = load_yaml(
        'dobot_moveit_config', 'config/kinematics.yaml'
    )

    core = Node(
        name="core",
        package="server-core-pkg",
        executable="core",
        output="screen",
        parameters=[robot_description, robot_description_semantic, kinematics_yaml],
        emulate_tty=True,
        prefix="xterm -e"
    )

    return LaunchDescription([
        core
    ])