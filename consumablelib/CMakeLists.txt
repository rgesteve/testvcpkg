cmake_minimum_required(VERSION 3.15)
project(consumablelib)

include (GNUInstallDirs)

add_library(consumablelib STATIC)
target_sources(consumablelib PRIVATE src/lib.cpp)
target_include_directories(consumablelib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_features(consumablelib PUBLIC cxx_std_11)
