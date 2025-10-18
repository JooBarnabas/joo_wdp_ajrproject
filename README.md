## ROS 2 C++ package. Static Badge

A package két node-ból áll. A . Megvalósítás ROS 2 Humble alatt.

# Packages and build
It is assumed that the workspace is ~/ros2_ws/.

# Clone the packages
```
cd ~/ros2_ws/src
git clone https://github.com/JooBarnabas/joo_wdp_ajrproject/
```
# Build ROS 2 packages
```
cd ~/ros2_ws
colcon build --packages-select distance_pkg --symlink-install
```
## Don't forget to source before ROS commands.
```
source ~/ros2_ws/install/setup.bash
```
# Run the package
```
ros2 run distance_pkg distance_nodes
```
# Graph
<img width="1117" height="72" alt="rosgraph" src="https://github.com/user-attachments/assets/4da8a8f9-ea88-400f-b8c8-7238faa10d5c" />

# Rviz
<img width="auto" height="auto" alt="rosgraph" src="https://github.com/user-attachments/assets/591a8c0b-b33e-4a4c-a804-c5503a0c7e04" />
<img width="auto" height="auto" alt="rosgraph" src="https://github.com/user-attachments/assets/d4376ed5-7aed-4463-9a0a-2a972bc8d292" />

