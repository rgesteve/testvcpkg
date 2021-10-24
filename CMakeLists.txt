cmake_minimum_required(VERSION 3.15)

project(fibo CXX)

include(CTest)

add_subdirectory(src)

if(BUILD_TESTING)
enable_testing()
add_subdirectory(tests)
endif()
