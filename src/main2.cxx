#include <iostream>
#include <vector>
//#include <algorithm>
#include <numeric>
#include <cstdlib>

using namespace std;

int main() {
  vector<int> vec{ 1, 2, 3, 4, 5}; 

  auto res = accumulate(begin(vec), end(vec), 0);
  cout << "Result is: " << res << "..." << endl;
  return EXIT_SUCCESS;
}
