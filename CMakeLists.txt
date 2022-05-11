# The following CMakeLists was adapted from the example found at 
# https://github.com/bast/cmake-example/blob/master/CMakeLists.txt

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(Maze)

enable_language(CXX)

set(CXX_STANDARD 11)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(safeguards)

message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")

# Check for the Operating Systems we test on, and define which we're on.
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_definitions(-DSYSTEM_LINUX)
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-DSYSTEM_WINDOWS)
endif()

# example how to set c++ compiler flags for GNU
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

include(git_revision)

configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/config.h.in
    ${PROJECT_BINARY_DIR}/config.h
)

find_package(OpenGL REQUIRED)
find_package(SFML 2.4 REQUIRED COMPONENTS system window)

include_directories(
    ${PROJECT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    deps/glad/include
    deps/glm
    )



set(SOURCE_FILES src/main.cpp
                 src/Game.cpp src/Game.hpp
                 src/Cell.cpp src/Cell.hpp
				 src/MazeGame.cpp src/MazeGame.hpp
				 src/Vertex.hpp
                 deps/glad/src/glad.c)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${SFML_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_link_libraries(${PROJECT_NAME} dl)
endif()
