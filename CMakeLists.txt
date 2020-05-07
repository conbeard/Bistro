cmake_minimum_required(VERSION 3.16)
project(Bistro)

set(CMAKE_CXX_STANDARD 17)

option(BISTRO_BUILD_SANDBOX "Build sandbox application" ON)

add_subdirectory(Bistro)

if (BISTRO_BUILD_SANDBOX)
    # Copy over shader files
    configure_file(${CMAKE_CURRENT_BINARY_DIR}/Bistro/Shaders/vertex.glsl ${CMAKE_CURRENT_BINARY_DIR}/Sandbox/Shaders/vertex.glsl COPYONLY)
    configure_file(${CMAKE_CURRENT_BINARY_DIR}/Bistro/Shaders/textureVertex.glsl ${CMAKE_CURRENT_BINARY_DIR}/Sandbox/Shaders/textureVertex.glsl COPYONLY)
    configure_file(${CMAKE_CURRENT_BINARY_DIR}/Bistro/Shaders/fragment.glsl ${CMAKE_CURRENT_BINARY_DIR}/Sandbox/Shaders/fragment.glsl COPYONLY)
    configure_file(${CMAKE_CURRENT_BINARY_DIR}/Bistro/Shaders/textureFragment.glsl ${CMAKE_CURRENT_BINARY_DIR}/Sandbox/Shaders/textureFragment.glsl COPYONLY)

    add_subdirectory(Sandbox)
endif ()
