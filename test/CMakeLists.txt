function(createTest NAME FILE)
    message(STATUS "createTest ${NAME} ${FILE}")
    add_executable(${NAME} EXCLUDE_FROM_ALL ${FILE})
    target_link_libraries(${NAME} ${ENGINE_LIB_NAME} glfw ${GLFW_LIBRARIES})
    add_dependencies(${NAME} ${ENGINE_LIB_NAME} glfw ${GLFW_LIBRARIES})
    add_dependencies(check ${NAME})
    add_test(NAME ${NAME} COMMAND $<TARGET_FILE:${NAME}>)
endfunction(createTest)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose -C $<CONFIGURATION>)

file(GLOB_RECURSE TEST_SRCS
     RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src
     *Test.cpp)

foreach(TESTFILE ${TEST_SRCS})
    get_filename_component(FILENAME ${TESTFILE} NAME_WE)
    createTest(${FILENAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/${TESTFILE}")
endforeach()


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
