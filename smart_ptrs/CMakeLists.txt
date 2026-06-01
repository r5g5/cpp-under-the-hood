cmake_minimum_required(VERSION 4.0)
project(cpp_under_the_hood)

set(CMAKE_CXX_STANDARD 11)

include_directories(../..)

set(HEADER_FILES unique_ptr.h)

add_executable(${PROJECT_NAME}
        ${HEADER_FILES})
