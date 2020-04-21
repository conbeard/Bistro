project(bistro-engine)

# Add Sources
set(BISTRO_SOURCES
        src/Bistro/Application.cpp
        src/Bistro/Log.cpp)

add_library(${PROJECT_NAME} SHARED ${BISTRO_SOURCES})
add_library(Bistro::Engine ALIAS ${PROJECT_NAME})

# Platform specific preprocessor defines
# PUBLIC  = define is visible to the user of Hazel
# PRIVATE = define is visible Hazel only
if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC B_PLATFORM_WINDOWS=1)
    target_compile_definitions(${PROJECT_NAME} PRIVATE B_BUILD_DLL=1)
endif()
if(APPLE)
    # for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
    target_compile_definitions(${PROJECT_NAME} PUBLIC B_PLATFORM_APPLE=1)
endif()
if(UNIX AND NOT APPLE)
    # for Linux, BSD, Solaris, Minix
    target_compile_definitions(${PROJECT_NAME} PUBLIC B_PLATFORM_UNIX=1)
endif()

# Set include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/Bistro)

# Language standard
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

find_package(spdlog REQUIRED)

# Link libraries (e.g. logging)
target_link_libraries(${PROJECT_NAME}
        spdlog::spdlog
        # ${CMAKE_THREAD_LIBS_INIT}     # Needed for unix builds to link to pthread
        # LOGGING
)

