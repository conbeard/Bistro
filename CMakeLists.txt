cmake_minimum_required(VERSION 3.16)
project(Bistro)

set(CMAKE_CXX_STANDARD 17)

option(BISTRO_BUILD_SANDBOX "Build sandbox application" ON)

add_subdirectory(Bistro)

if (BISTRO_BUILD_SANDBOX)
    add_subdirectory(Sandbox)
endif ()
