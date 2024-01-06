cmake_minimum_required(VERSION 2.8)

project(GLPhysics)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES src/*.cpp src/loader/*.cpp)
add_executable(GLPhysics ${SOURCES})

target_link_libraries(GLPhysics ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${GLM_LIBRARIES} glfw)

# copy shaders to build directory
file(COPY shaders models DESTINATION ${CMAKE_BINARY_DIR})
