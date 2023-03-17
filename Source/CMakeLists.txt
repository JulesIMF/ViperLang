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
#     CMakeLists for libviperlang.
#     LibViperLang contains main compiler possibilities.
#
# Author / Creation date:
#
#     JulesIMF / 17.03.23
#
# Revision History:
# 
# --
#


get_filename_component(LIB_PATH "." ABSOLUTE)

file(GLOB_RECURSE LIB_CXX_SOURCES ${LIB_PATH}/*.cpp)
file(GLOB_RECURSE LIB_HEADERS ${LIB_PATH}/*.hpp ${LIB_PATH}/*.ipp)

add_library(viperlang STATIC ${LIB_CXX_SOURCES} ${LIB_HEADERS})
target_link_libraries(viperlang PUBLIC fmt::fmt)

# Configure llvm

find_package(LLVM REQUIRED CONFIG)

target_include_directories(viperlang PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(viperlang PRIVATE ${llvm_libs})
add_definitions(${LLVM_DEFINITIONS})
add_compile_options(-Wall -Wextra -g)

llvm_map_components_to_libnames(llvm_libs support core irreader)

