cmake_minimum_required(VERSION 3.16)

project(UUVPlugins)

find_package(gz-sim8 REQUIRED)

add_library(
    ThrusterPlugin
    SHARED
    ThrusterPlugin.cpp
)

target_link_libraries(
    ThrusterPlugin
    gz-sim8::gz-sim8
)

install(
    TARGETS ThrusterPlugin
    LIBRARY DESTINATION lib
)