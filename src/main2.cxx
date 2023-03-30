#include <iostream>
#include <vector>
#include <ranges>
//#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>
#include <tuple>
#include <cstdlib>

// Apparently this is only implemented in MSVC for the moment
/*
#if __has_include(<format>) 
#   include <format> 
#else 
#   error format header is not available in this compiler
#endif 
*/

#include "fast-cpp-csv-parser/csv.h"

#include "sum_integers.hpp"

using namespace std;
namespace ranges = std::ranges;
namespace views = std::ranges::views;

void foo()
{
    std::tuple<std::string, int, double> person = {"John", 30, 175.5};
    auto [name, age, height] = person;

    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Height: " << height << std::endl;
    return;
}

int main() {
  vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8};

  for (int i : vec) { 
    cout << i << " "; 
  } 
  cout << endl;

  //auto rv = std::ranges::take_view(vec, 3);
  auto rv = ranges::take_view(vec, 3);
  for (auto v: rv) cout << v << " ";
  cout << endl;

  auto res1 = vec | views::transform([](int i) { return i * i; } );
  for (auto v: res1) cout << v << " ";
  cout << endl;

  // testing output with an ostream iterator
  copy(begin(vec), end(vec), ostream_iterator<int>(cout, ", "));
  cout << endl;

  auto res = accumulate(begin(vec), end(vec), 0);
  cout << endl << "Result of accumulate is: " << res << "..." << endl;

  foo();

  const string trainDatasetFilename { "iris.csv" };

  auto fullPath = get_full_path(trainDatasetFilename);
  if (fullPath.has_value()) {
    cout << "Got a value for the full path (" << fullPath.value() << "]\n";
  } else {
    cout << "An error trying out getting a full path for file" << "\n";
    return EXIT_FAILURE;
  }

  // Read data
  io::CSVReader<5> in(fullPath.value());
  // in.read_header(io::ignore_extra_column, "vendor", "size", "speed");

  // https://www.statology.org/iris-dataset-r/
  double sepal_length, sepal_width, petal_length, petal_width; 
  std::string species;
  while(in.read_row(sepal_length, sepal_width, petal_length, petal_width, species)) {
    cout << "Read data point of class [" << species << "]" << endl;
  }
  
  return EXIT_SUCCESS;
}
