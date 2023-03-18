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
#     Playground is a standalone app for testing new features.
#
# Author / Creation date:
#
#     JulesIMF / 19.03.23
#
# Revision History:
# 
# --
#

set(CMAKE_CXX_FLAGS "-O0")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${VIPER_PATH}/bin")
get_filename_component(TESTS_PATH "." ABSOLUTE)
file(GLOB_RECURSE TEST_SOURCES ${TESTS_PATH}/*.cpp)

add_executable(playground ${TEST_SOURCES})
target_link_libraries(playground PRIVATE viperlang)