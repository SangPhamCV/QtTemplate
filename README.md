# QtTemplate Project

## Overview
QtTemplate is a Qt/QML-based application designed for robot monitoring and control through ROS (Robot Operating System). The project provides a user interface for robot navigation, path planning, and virtual boundary creation.

The application connects to a ROS-enabled robot via WebSockets (ROSBridge) and communicates with the following functionality:

### ROS Messages Received:
- `/amcl_pose` (geometry_msgs/PoseWithCovarianceStamped): Robot position and orientation
- `/waypoints` (geometry_msgs/PoseArray): Navigation waypoints
- `/estimate_distance` (std_msgs/Float32): Estimated path distance
- `/remaining_distance` (std_msgs/Float32): Remaining distance to goal
- `/result_navigation` (std_msgs/String): Navigation completion status
- `/done_tracking` (std_msgs/String): Path tracking completion status
- `/armbot/mobile_base_controller/cmd_vel` (geometry_msgs/Twist): Current robot velocity

### ROS Messages Sent:
- `/armbot/mobile_base_controller/cmd_vel` (geometry_msgs/Twist): Velocity commands
- `/goal_position` (std_msgs/Float32MultiArray): Goal position data
- `/move_command` (std_msgs/String): Movement commands
- `/hermite_path` (nav_msgs/Path): Smooth path for robot to follow
- `/start_tracking` (std_msgs/String): Command to start path tracking
- `/virtual` (geometry_msgs/PoseArray): Virtual wall boundary points

> **Important Note**: This project implements only the control interface for robot monitoring and interaction. The actual movement algorithms, navigation parameters, and low-level control systems are handled by the ROS backend and are not included in this repository for security reasons.

## Architecture and Design Patterns

### Model-View-ViewModel (MVVM) Pattern
The application follows the MVVM pattern where:
- **Model**: C++ classes handling data and business logic (RosHandling, HermiteCurve, etc.)
- **View**: QML files defining the UI (Dashboard.qml, Login.qml)
- **ViewModel**: QObject-derived classes exposing properties and methods to QML via context properties

### Key Components

#### Backend (C++)
- **RosHandling**: Manages communication with ROS, handles robot pose and movement commands
- **RosBridgeClient**: WebSocket client for ROS Bridge protocol implementation
- **HermiteCurve**: Implements Hermite curve interpolation for smooth path planning
- **VirtualWall**: Manages virtual boundaries for robot navigation
- **ReadYaml**: Handles configuration loading and coordinate transformations
- **FileHandler**: Manages file operations for the application
- **LoginHandler**: Handles user authentication

#### Frontend (QML)
- **Main.qml**: Application entry point with conditional loading of Login or Dashboard
- **Dashboard.qml**: Main control interface for robot monitoring and control
- **Login.qml**: User authentication interface
- **CustomButton.qml**: Reusable button component

## Algorithms

### Hermite Curve Interpolation
The project uses Hermite curve interpolation for smooth path planning. This algorithm creates curved paths between control points that are both visually appealing and suitable for robot navigation. Key aspects include:

- Uses cubic Hermite spline interpolation to generate smooth curves
- Implements a tension parameter to control the tightness of curves
- Creates paths with continuous first derivatives for smooth robot motion

### Virtual Wall Generation
Virtual walls define boundaries the robot should not cross. The implementation uses:

- Bresenham's line algorithm to create a series of points between two endpoints
- Coordinate transformation to convert between pixel and meter spaces
- Point-to-point connections to form continuous boundary lines

### Coordinate Transformation
The application converts between screen coordinates (pixels) and real-world coordinates (meters) using:

- Linear transformation based on map resolution and origin
- Scaling factors derived from display dimensions
- Offset adjustments for UI element positioning
- YAML configuration parameters for map properties

## Getting Started

### Prerequisites
- Qt 5 (with Quick, WebSockets, WebEngine components)
- yaml-cpp library

### Building the Project
```bash
mkdir build && cd build
cmake ..
make
```

### Running the Application
```bash
./MyQmlProject
```
