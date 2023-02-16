cmake_minimum_required(VERSION 3.10)

# set the project name
project(Algorithm)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(Algorithm main.cpp 
                            gen_random_value.h gen_random_value.cpp
                            mcmc.h mcmc.cpp
                            get_norm.h get_norm.cpp
                            generate_graph.h generate_graph.cpp
                            gk2_algorithm.h gk2_algorithm.cpp
                            gk1_algorithm.h gk1_algorithm.cpp
                            map_heap.h map_heap.cpp)