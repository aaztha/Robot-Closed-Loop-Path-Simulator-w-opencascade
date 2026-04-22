cmake_minimum_required(VERSION 3.16)
project(RobotPathSim)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Adjust OpenCASCADE path if needed
find_package(OpenCASCADE REQUIRED)

add_executable(RobotPathSim
    main.cpp
    Viewer.cpp
)

target_include_directories(RobotPathSim PRIVATE ${OpenCASCADE_INCLUDE_DIR})
target_link_libraries(RobotPathSim Qt6::Widgets ${OpenCASCADE_LIBRARIES})