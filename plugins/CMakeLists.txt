cmake_minimum_required(VERSION 3.16)

project(UUVPlugins)

find_package(gz-sim8 REQUIRED)

# --------------------------------------------------
# Thruster Plugin
# --------------------------------------------------
# add_library(
#     ThrusterPlugin
#     SHARED
#     ThrusterPlugin.cpp
# )

# target_link_libraries(
#     ThrusterPlugin
#     gz-sim8::gz-sim8
# )

# --------------------------------------------------
# Hydrodynamics Plugin
# --------------------------------------------------
add_library(
    HydrodynamicsPlugin
    SHARED
    HydrodynamicsPlugin.cpp
)

target_link_libraries(
    HydrodynamicsPlugin
    gz-sim8::gz-sim8
)

# --------------------------------------------------
# FinPlugin Plugin
# --------------------------------------------------
# add_library(
#     FinPlugin
#     SHARED
#     FinPlugin.cpp
# )

# target_link_libraries(
#     FinPlugin
#     gz-sim8::gz-sim8
# )

# --------------------------------------------------
# StateEstimatorPlugin Plugin
# --------------------------------------------------
add_library(
    StateEstimatorPlugin
    SHARED
    StateEstimatorPlugin.cpp
)

target_link_libraries(
    StateEstimatorPlugin
    gz-sim8::gz-sim8
)

# --------------------------------------------------
# DepthSensorPlugin Plugin
# --------------------------------------------------
# add_library(DepthSensorPlugin SHARED
#     DepthSensorPlugin.cpp)

# target_link_libraries(DepthSensorPlugin
#     gz-sim8::gz-sim8
#     gz-transport13::gz-transport13
#     gz-msgs10::gz-msgs10)

# --------------------------------------------------
# VelocitySensorPlugin Plugin
# --------------------------------------------------
# add_library(VelocitySensorPlugin SHARED
#     VelocitySensorPlugin.cpp)

# target_link_libraries(VelocitySensorPlugin
#     gz-sim8::gz-sim8)

# --------------------------------------------------
# ActuatorPlugin Plugin
# --------------------------------------------------
add_library(ActuatorPlugin SHARED
    ActuatorPlugin.cpp)

target_include_directories(
    ActuatorPlugin
    PRIVATE
    ${CMAKE_SOURCE_DIR}/plugins)


target_link_libraries(
    ActuatorPlugin
    PRIVATE
    gz-sim8::gz-sim8
    gz-transport13::gz-transport13
    gz-msgs10::gz-msgs10)

# --------------------------------------------------
# Install
# --------------------------------------------------
install(
    TARGETS HydrodynamicsPlugin StateEstimatorPlugin  ActuatorPlugin
    LIBRARY DESTINATION lib
)