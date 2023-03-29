#include <iostream>
#include <vector>
#include <ranges>
//#include <algorithm>
#include <numeric>
#include <cstdlib>

// Apparently this is only implemented in MSVC for the moment
/*
#if __has_include(<format>) 
#   include <format> 
#else 
#   error format header is not available in this compiler
#endif 
*/

using namespace std;
namespace ranges = std::ranges;
namespace views = std::ranges::views;

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

  auto res = accumulate(begin(vec), end(vec), 0);
  cout << endl << "Result of accumulate is: " << res << "..." << endl;
  return EXIT_SUCCESS;
}
