cmake_minimum_required(VERSION 3.8)
project(text_subscriber)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# External Package for custom message located here
find_package(custom_msg_pkg REQUIRED)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Executable created and named custm_msg_sub
add_executable(cstm_msg_sub src/subscriber.cpp)

# Executable linked with libraries required
ament_target_dependencies(cstm_msg_sub rclcpp custom_msg_pkg)

# Compiled files installed into Ros 2 Workspace
install(TARGETS
  cstm_msg_sub
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()