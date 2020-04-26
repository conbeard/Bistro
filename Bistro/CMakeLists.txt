project(bistro-engine)

# Add Sources
set(BISTRO_SOURCES
        src/Bistro/Application.cpp
        src/Bistro/Log.cpp
        src/Bistro/Layer.cpp
        src/Bistro/LayerStack.cpp
        src/Bistro/ImGui/ImGuiLayer.cpp
        src/Bistro/ImGui/ImGuiBuild.cpp
        src/Bistro/Renderer/Shader.cpp
        src/Bistro/Renderer/Buffer.cpp
        src/Bistro/Renderer/Renderer.cpp
        src/Platform/MacOS/MacInput.cpp
        src/Platform/MacOS/MacWindow.cpp
        src/Platform/OpenGL/OpenGLContext.cpp
        src/Platform/OpenGL/OpenGLBuffer.cpp
        )

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

target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)

# Set include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/Bistro)

# Language standard
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
# Precompiled Headers
target_precompile_headers(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/src/bpch.h")

find_package(spdlog REQUIRED)
find_package(glfw3 REQUIRED)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glm REQUIRED)

# Link libraries (e.g. logging)
target_link_libraries(${PROJECT_NAME}
        spdlog::spdlog
        glfw
        glad
        imgui
        glm
)

