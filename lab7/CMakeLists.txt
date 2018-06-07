cmake_minimum_required(VERSION 3.9)
project(lab7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework OpenGl")
set(CMAKE_CXX_STANDARD 11)
set(GLFW_USE_CHDIR)
set(GLFW_USE_MENUBAR)
set(GLFW_USE_RETINA)

set(SOURCES_FILES main.cpp Circle.cpp Circle.h Cone.cpp Cone.h projections.h Level.cpp Level.h Cube.cpp Cube.h Vertex.cpp
        Vertex.h MyVector.cpp MyVector.h textureThings.h lightThings.h globalVarsAndCallbacks.h timeThings.h definitions.h)

add_executable(lab7 ${SOURCES_FILES})

target_link_libraries(lab7 GLEW GLFW)