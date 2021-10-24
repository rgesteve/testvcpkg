# Testing
# testing binary
add_executable(cpp_test test.cxx)
target_link_libraries(cpp_test sum_integers)

# define tests
add_test(
  NAME cpp_test2
  COMMAND $<TARGET_FILE:cpp_test>
)
