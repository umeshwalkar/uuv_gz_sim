cmake_minimum_required(VERSION 3.16)

project(UUVPlugins)

find_package(gz-sim8 REQUIRED)

# --------------------------------------------------
# Thruster Plugin
# --------------------------------------------------
add_library(
    ThrusterPlugin
    SHARED
    ThrusterPlugin.cpp
)

target_link_libraries(
    ThrusterPlugin
    gz-sim8::gz-sim8
)

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
add_library(
    FinPlugin
    SHARED
    FinPlugin.cpp
)

target_link_libraries(
    FinPlugin
    gz-sim8::gz-sim8
)

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
add_library(DepthSensorPlugin SHARED
    DepthSensorPlugin.cpp)

target_link_libraries(DepthSensorPlugin
    gz-sim8::gz-sim8
    gz-transport13::gz-transport13
    gz-msgs10::gz-msgs10)

# --------------------------------------------------
# VelocitySensorPlugin Plugin
# --------------------------------------------------
add_library(VelocitySensorPlugin SHARED
    VelocitySensorPlugin.cpp)

target_link_libraries(VelocitySensorPlugin
    gz-sim8::gz-sim8)

# --------------------------------------------------
# Install
# --------------------------------------------------
install(
    TARGETS ThrusterPlugin HydrodynamicsPlugin FinPlugin StateEstimatorPlugin DepthSensorPlugin VelocitySensorPlugin
    LIBRARY DESTINATION lib
)