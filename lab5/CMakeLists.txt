cmake_minimum_required(VERSION 3.9)
project(lab5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework OpenGl")
set(CMAKE_CXX_STANDARD 11)
set(GLFW_USE_CHDIR)
set(GLFW_USE_MENUBAR)
set(GLFW_USE_RETINA)

set(SOURCES_FILES main.cpp Figure.cpp Figure.h Point.cpp Point.h)

add_executable(lab5 ${SOURCES_FILES})

target_link_libraries(lab5 GLEW GLFW)