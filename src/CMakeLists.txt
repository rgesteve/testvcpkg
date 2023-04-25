set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

# message("**** Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

find_package(fmt REQUIRED)
find_package(range-v3 REQUIRED)
find_package(cxxopts REQUIRED)

#rapidcsv is header-only so, instead of
#  find_package(rapidcsv REQUIRED)
# we should use
find_path(RAPIDCSV_INCLUDE_DIRS "rapidcsv.h")

option(RUN_XGBOOST_KERNEL "Include the XGBoost example" OFF)
if(RUN_XGBOOST_KERNEL)
  find_package(xgboost REQUIRED)

  # xgboost is built as static libraries, all cxx dependencies need to be linked into the
  # executable.
  if(XGBOOST_BUILD_STATIC_LIB)
    enable_language(CXX)
    # find again for those  cxx libraries.
    find_package(xgboost REQUIRED)
  endif(XGBOOST_BUILD_STATIC_LIB)
endif(RUN_XGBOOST_KERNEL)

option(RUN_ONEDAL_KERNEL "Include the OneDAL example" OFF)
if(RUN_ONEDAL_KERNEL)
  set(USE_DPCPP no)
  find_package(oneDAL CONFIG REQUIRED)
  #
  include_directories(${oneDAL_INCLUDE_DIRS})
  link_libraries(${oneDAL_IMPORTED_TARGETS})
endif(RUN_ONEDAL_KERNEL)

find_path(FAST_CPP_CSV_PARSER_INCLUDE_DIRS "fast-cpp-csv-parser/csv.h")

# example library
add_library(sum_integers SHARED sum_integers.cxx)

# main code
add_executable(fibo main.cxx)
target_compile_features(fibo PRIVATE cxx_std_17)
target_include_directories(fibo PRIVATE ${RAPIDCSV_INCLUDE_DIRS})
target_link_libraries(fibo
  PRIVATE
    fmt::fmt
    range-v3::range-v3
    cxxopts::cxxopts
    stdc++fs
#    xgboost::xgboost
sum_integers)

add_executable(onemore main2.cxx)
target_compile_features(onemore PRIVATE cxx_std_20)
target_compile_options(onemore PRIVATE -fpermissive)
target_include_directories(onemore PRIVATE ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS})
target_link_libraries(onemore
  PRIVATE
  xgboost::xgboost
#    stdc++fs
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
