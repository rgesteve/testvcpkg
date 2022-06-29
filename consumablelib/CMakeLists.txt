cmake_minimum_required(VERSION 3.15)
project(consumablelib
  VERSION "0.0.1"
  )

include (GNUInstallDirs)

set(consumablelib_INSTALL_CMAKEDIR cmake CACHE PATH "Installation directory for config-file package cmake files")

add_library(consumablelib STATIC)
target_sources(consumablelib PRIVATE src/lib.cpp)
target_include_directories(consumablelib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )
target_compile_features(consumablelib PUBLIC cxx_std_11)

install(TARGETS consumablelib
  EXPORT consumablelib_export
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDE_DIRS})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT consumablelib_export
  FILE consumablelib-config.cmake
  NAMESPACE consumablelib::
  DESTINATION ${consumablelib_INSTALL_CMAKEDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file("consumablelib-config-version.cmake"
  COMPATIBILITY SameMajorVersion)
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/consumablelib-config-version.cmake"
  DESTINATION "${consumablelib_INSTALL_CMAKEDIR}")

