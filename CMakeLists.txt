cmake_minimum_required(VERSION 3.0.2)
project(a65)

add_library(a65 parser.cpp utils.cpp)

add_executable(a65.bin main.cpp)
target_link_libraries(a65.bin a65)

target_compile_options(a65 PUBLIC -std=c++17 -Wall -Wextra)
target_compile_options(a65.bin PUBLIC -std=c++17 -Wall -Wextra)

add_subdirectory(tests)

