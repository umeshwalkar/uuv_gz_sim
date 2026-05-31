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
# Install
# --------------------------------------------------
install(
    TARGETS ThrusterPlugin HydrodynamicsPlugin
    LIBRARY DESTINATION lib
)