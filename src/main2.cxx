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

#undef _EXPANDED_DATASET_SCHEMA_
//#define USE_IRIS
#undef USE_IRIS

#ifndef USE_IRIS
#define DATASET_FILENAME "boston_housing.csv"
#define HAS_HEADERS 1

/* CRIM,ZN,INDUS,CHAS,NOX,RM,AGE,DIS,RAD,TAX,PTRATIO,B,LSTAT,MEDV */
using RowType = std::tuple<float,float,float,float,float,float,float,float,float,float,float,float,float,float>;
#else
#define DATASET_FILENAME "iris.csv"
#define HAS_HEADERS 0

/* sepal_length, sepal_width, petal_length, petal_width, species : string */
using RowType = std::tuple<double, double, double, double, std::string>;
#endif

using namespace std;
namespace ranges = std::ranges;
namespace views = std::ranges::views;

const size_t RowTypeSize = tuple_size_v<RowType>;

template<std::size_t... Idx, typename T, typename R>
bool read_row_helper(std::index_sequence<Idx...>, T& row, R& reader)
{
  return reader.read_row(std::get<Idx>(row)...);
}

template<std::size_t... Idx, typename T, typename S>
void fill_values(std::index_sequence<Idx...>, T& row, std::vector<S>& data)
{
  data.insert(end(data), { std::get<Idx>(row)... });
}

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

  const string trainDatasetFilename { DATASET_FILENAME };

  auto fullPath = get_full_path(trainDatasetFilename);
  if (fullPath.has_value()) {
    cout << "Got a value for the full path (" << fullPath.value() << "]\n";
  } else {
    cout << "An error trying out getting a full path for file" << "\n";
    return EXIT_FAILURE;
  }

  // Read data
  io::CSVReader<RowTypeSize> in(fullPath.value());
  if (HAS_HEADERS) {
    // in.read_header(io::ignore_extra_column, "vendor", "size", "speed");
    in.next_line();
  }

#ifdef _EXPANDED_DATASET_SCHEMA_
  // https://www.statology.org/iris-dataset-r/
  double sepal_length, sepal_width, petal_length, petal_width; 
  std::string species;
  while(in.read_row(sepal_length, sepal_width, petal_length, petal_width, species)) {
    cout << "Read data point of class [" << species << "]" << endl;
  }
#else
  bool done = false;
  size_t read_rows = 0;
  RowType row;
#ifdef USE_IRIS
  vector<string> labels;
  vector<double> features;
#else
    vector<float> labels;
    vector<float> features;
#endif

  while (!done) {
    done = !read_row_helper(make_index_sequence<RowTypeSize>{}, row, in);
    if (!done) {
      // cout << "The label in this row is: [" << std::get<RowTypeSize - 1>(row) << " ]." << endl;
      labels.push_back(std::get<RowTypeSize - 1>(row));
      fill_values(std::make_index_sequence<RowTypeSize - 1>{}, row, features);
      read_rows++;
    }
  }
  cout << "Read: " << read_rows << " rows, labels is has now " << labels.size() <<" elements, " 
       << "and features has: " << features.size() << " elements, a sampling of which is: "  << endl;
  const size_t SAMPLE_SIZE = 5;
  auto check_view = ranges::take_view(features, SAMPLE_SIZE * RowTypeSize);
  copy(begin(check_view), end(check_view), ostream_iterator<double>(cout, ", "));
  cout << endl;
#endif
  
  return EXIT_SUCCESS;
}
