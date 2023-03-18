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
#     Main CMakeLists.
#     Describes project structure.
#
# Author / Creation date:
#
#     JulesIMF / 09.02.23
#
# Revision History:
# 
# --
#

cmake_minimum_required(VERSION 3.16)
project(Viper)

# --------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
get_filename_component(VIPER_PATH "." ABSOLUTE)

add_compile_options(-Wall -Wextra -g)

# --------------------------------------------------------------------

find_package(fmt REQUIRED)
find_package(Catch2 2 REQUIRED)

# --------------------------------------------------------------------

include_directories(Includes)
add_subdirectory(Source)
add_subdirectory(Playground)
add_subdirectory(Tests)

# --------------------------------------------------------------------
