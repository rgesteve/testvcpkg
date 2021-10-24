find_package(fmt REQUIRED)
find_package(range-v3 REQUIRED)
find_package(cxxopts REQUIRED)

# example library
add_library(sum_integers sum_integers.cxx)

# main code
add_executable(fibo main.cxx)
target_compile_features(fibo PRIVATE cxx_std_17)
target_link_libraries(fibo
  PRIVATE
    fmt::fmt
    range-v3::range-v3
    cxxopts::cxxopts
    sum_integers)
