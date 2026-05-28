cmake_minimum_required(VERSION 4.2)
project(discard_args)

add_library(discard_args INTERFACE include/discard_args.h)
target_include_directories(discard_args INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_compile_features(discard_args INTERFACE cxx_std_17)


function(add_example name)
    add_executable(${name} ${ARGN})
    target_compile_features(${name} PRIVATE cxx_std_17)
    target_link_libraries(${name} PRIVATE discard_args)
endfunction()


add_example(example1 examples/example_1.cpp)
add_example(example2 examples/example_2.cpp)
add_example(example3 examples/example_3.cpp)