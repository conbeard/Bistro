cmake_minimum_required(VERSION 3.0)
project(stb)

add_library(stb_image stb_image.cpp stb_image.h)
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
