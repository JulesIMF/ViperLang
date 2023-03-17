# ++
#
# Copyright (c) 2023 JulesIMF, MIPT
#
# Module Name:
#
#     CMakeLists.txt
#
# Abstract:
#
#     CMakeLists for tests.
#
# Author / Creation date:
#
#     JulesIMF / 10.02.23
#
# Revision History:
# 
# --
#

message(STATUS "Generating tests")

get_filename_component(TESTS_PATH "." ABSOLUTE)
file(GLOB_RECURSE TEST_SOURCES ${TESTS_PATH}/*.cpp)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE viperlang)
target_link_libraries(tests PRIVATE Catch2::Catch2)
