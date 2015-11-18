cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)

set(ENGINE_NAME graplengine)

project(${ENGINE_NAME})

# Preamble

if (CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)
    message(FATAL_ERROR "Source and binary directories must be different")
endif()

if (MSVC)
    set(BINARY_DIRECTORY build)
endif()

if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR
    ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR
    (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel") AND UNIX))

    set(LANGUAGE_STANDARD "c++11")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CSS_LANGUAGE_STANDARD ${LANGUAGE_STANDARD})
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    set(CMAKE_CXX_FLAGS "-std=${LANGUAGE_STANDARD}")
endif()

# Executable

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

add_executable(${ENGINE_NAME} src/main.cpp)

# Dependent libraries

find_package(OpenGL)

if(APPLE)
    include_directories(${OPENGL_INCLUDE_DIR}/Headers)
else()
    include_directories(${OPENGL_INCLUDE_DIR})
endif()

include_directories(${ENGINE_NAME} ${OPENGL_LIBRARIES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)


# Output directory

if(MSVC)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(COPY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/Debug/ )
    else()
        set(COPY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/Release/ )
    endif()
else()
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/Debug )
    else()
        set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/Release )
    endif()
endif()

# Sub directories
enable_testing()
add_subdirectory(test)

