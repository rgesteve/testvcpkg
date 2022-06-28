cmake_minimum_required(VERSION 3.15)
project(packing_try
  VERSION 0.0.1
  DESCRIPTION "Testing the installation/packaging capabilities of cmake/cpack"
  LANGUAGES CXX)

add_executable(packaging_try)
target_sources(packaging_try PRIVATE src/main.cpp)
target_compile_features(packaging_try PRIVATE cxx_std_11)

