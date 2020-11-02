cmake_minimum_required(VERSION 3.17)
project(lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab3 main.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(lab3 PUBLIC OpenMP::OpenMP_CXX)
endif()
