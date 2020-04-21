project(bistro-sandbox)

# Add source files
set(SANDBOX_SOURCES
        src/main.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SANDBOX_SOURCES})
# Set include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
# Compiler standard
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
# Link libraries
target_link_libraries(${PROJECT_NAME} Bistro::Engine)

