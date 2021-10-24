#include <cxxopts.hpp>
#include <fmt/format.h>
#include <range/v3/view.hpp>

#include <filesystem>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cstdlib>

#include "sum_integers.hpp"

namespace view = ranges::views;

int fib(int x) {
  int a = 0, b = 1;

  for (int it : view::repeat(0) | view::take(x)) {
    (void)it;
    int tmp = a;
    a += b;
    b = tmp;
  }

  return a;
}

using namespace std;

int main(int argc, char** argv) {
#if 0
  cxxopts::Options options("fibo", "Print the fibonacci sequence up to a value 'n'");
    options.add_options()
      ("n,value", "The value to print to", cxxopts::value<int>()->default_value("10"));

  auto result = options.parse(argc, argv);
  auto n = result["value"].as<int>();

  for (int x : view::iota(1) | view::take(n)) {
    fmt::print("fib({}) = {}\n", x, fib(x));
  }

  std::cout << std::endl;

  // Print the names of all regular files in the current directory
  std::filesystem::directory_iterator begin("."), end;
  for (auto iter = begin; iter != end; ++iter) {
    if (iter->is_regular_file()) {
  	  std::cout << iter->path().filename() << '\n';
  	}
  }
#endif

  const size_t N = 10;
  vector<int> data(N); 

  cout << "Running from self-contained cmake" << endl;

  cout << "Creating data: \n";
  iota(begin(data), end(data), -5); 
  copy(begin(data), end(data), ostream_iterator<int>{cout, ", "});
  cout << '\n';

  cout << "The result of summing is: [" << sum_integers(data) << "]" << endl;

  cout << "Done!!" << endl;

  return EXIT_SUCCESS;
}
