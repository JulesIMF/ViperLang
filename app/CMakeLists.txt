add_executable(repl repl.cpp)
add_compile_options(-Wall -Wextra -g)
target_link_libraries(repl PUBLIC compiler)
