function(createTest NAME FILE)
    add_executable(${NAME} EXCLUDE_FROM_ALL ${FILE})
    add_test(NAME ${NAME} COMMAND $<TARGET_FILE:${NAME}>)
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose
        DEPENDS ${NAME})
endfunction(createTest)

file(GLOB_RECURSE TEST_SRCS
     RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src
     *Test.cpp)

foreach(FILE "${TEST_SRCS}")
    get_filename_component(FILENAME ${FILE} NAME_WE)
    createTest(${FILENAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/${FILE}")
endforeach()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
