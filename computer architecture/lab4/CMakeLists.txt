cmake_minimum_required(VERSION 3.10)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

add_executable(lab4 main.cpp)

target_link_libraries(lab4 ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
    set_target_properties(lab4 PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(Lab3 PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()