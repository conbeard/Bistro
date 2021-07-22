project(bistro-engine)

# Add Sources
set(BISTRO_SOURCES
        src/Bistro/Core/Application.cpp
        src/Bistro/Core/Log.cpp
        src/Bistro/Core/Layer.cpp
        src/Bistro/Core/LayerStack.cpp
        src/Bistro/OrthographicCameraController.cpp
        src/Bistro/ImGui/ImGuiLayer.cpp
        src/Bistro/ImGui/ImGuiBuild.cpp
        src/Bistro/Renderer/Shader.cpp
        src/Bistro/Renderer/Buffer.cpp
        src/Bistro/Renderer/Renderer.cpp
        src/Bistro/Renderer/Renderer2D.cpp
        src/Bistro/Renderer/RendererAPI.cpp
        src/Bistro/Renderer/RenderCommand.cpp
        src/Bistro/Renderer/Texture.cpp
        src/Bistro/Renderer/VertexArray.cpp
        src/Bistro/Renderer/OrthographicCamera.cpp
        src/Platform/MacOS/MacInput.cpp
        src/Platform/MacOS/MacWindow.cpp
        src/Platform/OpenGL/OpenGLShader.cpp
        src/Platform/OpenGL/OpenGLContext.cpp
        src/Platform/OpenGL/OpenGLBuffer.cpp
        src/Platform/OpenGL/OpenGLVertexArray.cpp
        src/Platform/OpenGL/OpenGLRendererAPI.cpp
        src/Platform/OpenGL/OpenGLTexture.cpp
        )

add_library(${PROJECT_NAME} STATIC ${BISTRO_SOURCES})
add_library(Bistro::Engine ALIAS ${PROJECT_NAME})

# Platform specific preprocessor defines
# PUBLIC  = define is visible to the user of Bistro
# PRIVATE = define is visible Bistro only
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

#============================================
# Dependencies
#============================================
find_package(spdlog REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

add_subdirectory(vendor/glad)

add_library(imgui SHARED
        vendor/imgui/imgui.h
        vendor/imgui/imconfig.h
        vendor/imgui/imgui_internal.h
        vendor/imgui/imstb_rectpack.h
        vendor/imgui/imstb_textedit.h
        vendor/imgui/imstb_truetype.h
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_widgets.cpp
        )

target_link_libraries(imgui glad glfw)

target_include_directories(imgui
        PUBLIC
        $<INSTALL_INTERFACE:imgui>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui>
        )

add_subdirectory(vendor/glm REQUIRED)
add_subdirectory(vendor/stb_image)

# Link libraries (e.g. logging)
target_link_libraries(${PROJECT_NAME}
        spdlog::spdlog
        glfw
        glad
        imgui
        glm
        stb_image
)

