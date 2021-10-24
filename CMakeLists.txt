cmake_minimum_required(VERSION 3.15)

project(fibo CXX)

include(CTest)

if(BUILD_TESTING)
enable_testing()
endif()

add_subdirectory(src)
