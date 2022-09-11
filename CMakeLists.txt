cmake_minimum_required(VERSION 3.17)
project(Mandelbrot)

set(APP_NAME "Mandelbrot Explorer")
set(APP_BUNDLE_IDENTIFIER "co.kev1n.Mandelbrot")

# Setup libraries
include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG master)
FetchContent_Declare(glad GIT_REPOSITORY https://github.com/kevinoverflow/glad.git GIT_TAG main)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glad)

# Setup resources
file(GLOB RESOURCE_FILES
    "resources/FragmentShader.fs"
    "resources/VertexShader.vs"
)

# Setup executable
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} 
    "src/*.c"
    "src/*.h")

add_executable(${PROJECT_NAME} 
    "src/main.c"
    ${SOURCES}
    ${RESOURCE_FILES}
    )
target_include_directories(${PROJECT_NAME} PUBLIC "src")
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw)

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 99
    EXECUTABLE_NAME ${APP_NAME}
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_BUNDLE_NAME ${APP_BUNDLE_IDENTIFIER}
    RESOURCE "${RESOURCE_FILES}")