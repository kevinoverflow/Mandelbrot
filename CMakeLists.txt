cmake_minimum_required(VERSION 3.0)

# Set project name
project(Mandelbrot)

# Set C++11 as the required language standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find installed GLFW and GLEW libraries
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(CMakeRC REQUIRED)

# Add include directories
include_directories(
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

# Set source directory
set(SOURCE_DIR src)

# Add all source files
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.h")

# Add executable
add_executable(Mandelbrot ${SOURCES})

# Add Resources
cmrc_add_resource_library(resources
    NAMESPACE res
    WHENCE shaders
    shaders/FragmentShader.frag
    shaders/VertexShader.vert)

# Link libraries
target_link_libraries(Mandelbrot
    glfw
    GLEW::GLEW
    resources)