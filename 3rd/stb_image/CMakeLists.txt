cmake_minimum_required(VERSION 3.12)

add_library(stb_image STATIC
    stb_image.h
    stb_image.cpp
)

target_include_directories(stb_image INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
