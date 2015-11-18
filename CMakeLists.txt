cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)

set(ENGINE_NAME graplengine)

project(${ENGINE_NAME})
enable_testing()

# Preamble

if (CMAKE_CURRENT_SOURCE_DIR equal CMAKE_CURRENT_BINARY_DIR)
    message(FATAL_ERROR "Source and binary directories must be different")
endif()

if (MSVC)
    set(BINARY_DIRECTORY build)
endif()

if (("${CMAKE_CXX_COMPILER_ID}" strequal "Clang") OR
    ("${CMAKE_CXX_COMPILER_ID}" strequal "GNU") OR
    (("${CMAKE_CXX_COMPILER_ID}" strequal "Intel") and UNIX))

    set(LANGUAGE_STANDARD "c++11")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CSS_LANGUAGE_STANDARD ${LANGUAGE_STANDARD})
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    set(CMAKE_CXX_FLAGS "-std=${LANGUAGE_STANDARD}")
endif()

# Dependent libraries

find_package(OpenGL)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${ENGINE_NAME} ${OPENGL_LIBRARIES})

# Executable

ADD_EXECUTABLE(${ENGINE_NAME} src/main.cpp)
