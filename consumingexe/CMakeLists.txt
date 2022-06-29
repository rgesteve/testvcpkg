cmake_minimum_required(VERSION 3.15)
project(consumingexe)

find_package(consumablelib 0 CONFIG REQUIRED)

message(STATUS "Found version ${consumablelib_VERSION} of the consumablelib library")
get_property(_inc TARGET consumablelib::consumablelib PROPERTY LOCATION)
message(STATUS "thinking this is the include dir ${_inc} of the consumablelib library")
add_executable(consumingexe src/main.cpp)
target_compile_features(consumingexe PRIVATE cxx_std_11)

#target_include_directories(consumingexe INTERFACE consumablelib::consumablelib)
target_link_libraries(consumingexe PRIVATE consumablelib::consumablelib)

