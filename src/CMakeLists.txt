set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

# message("**** Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

find_package(fmt REQUIRED)
find_package(range-v3 REQUIRED)
find_package(cxxopts REQUIRED)

set(USE_DPCPP no)
find_package(oneDAL CONFIG REQUIRED)

include_directories(${oneDAL_INCLUDE_DIRS})
link_libraries(${oneDAL_IMPORTED_TARGETS})

# example library
add_library(sum_integers SHARED sum_integers.cxx)

# main code
add_executable(fibo main.cxx)
target_compile_features(fibo PRIVATE cxx_std_17)
target_link_libraries(fibo
  PRIVATE
    fmt::fmt
    range-v3::range-v3
    cxxopts::cxxopts
    stdc++fs
    sum_integers)

# Testing
# testing binary
#add_executable(cpp_test test.cxx)
#target_link_libraries(cpp_test sum_integers)

#if(BUILD_TESTING)
# define tests
#add_test(
#  NAME cpp_test
#  COMMAND $<TARGET_FILE:cpp_test>
#  )
#endif()
