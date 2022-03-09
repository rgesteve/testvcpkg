#if 0
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

  const size_t N = 10;
  vector<int> data(N); 

  cout << "Running from self-contained cmake" << endl;

  cout << "Creating data: \n";
  iota(std::begin(data), std::end(data), -5); 
  copy(std::begin(data), std::end(data), ostream_iterator<int>{cout, ", "});
  cout << '\n';

  cout << "The result of summing is: [" << sum_integers(data) << "]" << endl;

  cout << "Done!!" << endl;

  return EXIT_SUCCESS;
}
#else
#include <iostream>
#include <string>
#include <random>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <filesystem>

#include "daal.h"

using namespace std;
using namespace daal;
using namespace daal::data_management;
using namespace daal::algorithms;

const unsigned int SIZE = 128;
const unsigned int ITER = 4;

const string trainDatasetFilename = "titanic_train.csv";

int main(int argc, char* argv[])
{
  #if 0
  vector<double> data(SIZE);
  random_device rd;
  default_random_engine rng(rd());

  for (auto i = 0; i < ITER; ++i) {
    generate(begin(data), end(data), [&rng] { return generate_canonical<double, 12>(rng); });
    copy(begin(data), end(data), ostream_iterator<double>(cout, " "));
    cout << endl;
  }
  #endif

  auto dataset_path_name = std::getenv("DATASET_PATH");
  if (dataset_path_name == NULL) {
    std::cerr << "Need DATASET_PATH variable defined, couldn't find\n";
    return EXIT_FAILURE;
  }
  auto dataset_path = std::filesystem::path(dataset_path_name);
  if (!std::filesystem::exists(dataset_path)) {
    std::cerr << "Cannot find specified path for dataset (" << dataset_path << ")\n";
    return EXIT_FAILURE;
  }

  if (!std::filesystem::exists(dataset_path / trainDatasetFilename)) {
    std::cerr << "Cannot find expected file on the path specified (" << dataset_path << ")\n";
    return EXIT_FAILURE;
  }

  auto dataset_full_path = dataset_path / trainDatasetFilename;

#if 0
  auto path = std::filesystem::current_path();
  if (std::filesystem::exists(path)) {
    std::cout << "current path exists" << '\n';
  } else {
    std::cout << "Really weird" << '\n';
  }


  std::cout << std::filesystem::relative(dataset_path) << '\n';
  std::cout << std::filesystem::canonical(dataset_path) << '\n';
  std::cout << std::filesystem::absolute(dataset_path) << '\n';

  std::cout << "The name in character (" << dataset_path.c_str() << ")\n";
#endif
  std::cout << "Starting to load data from [" << dataset_full_path.string() << "]\n";

  typedef float FPType;
  const unsigned int nFeatures = 3;
  const unsigned int nDependentVariables = 1;
  FileDataSource<CSVFeatureManager> trainDataSource(dataset_full_path.string(), DataSource::doAllocateNumericTable, DataSource::doDictionaryFromContext);

#if 0
  // These trigger a compile error
  NumericTable trainData(new HomogenNumericTable<FPType>(nFeatures, 0, NumericTable::notAllocate));
  NumericTable trainDependentVariables(new HomogenNumericTable<FPType>(nDependentVariables, 0, NumericTable::notAllocate));
#else
  NumericTablePtr trainData;
  NumericTablePtr trainDependentVariables;
  trainData.reset(new HomogenNumericTable<>(nFeatures, 0, NumericTable::notAllocate));
  trainDependentVariables.reset(new HomogenNumericTable<>(nDependentVariables, 0, NumericTable::notAllocate));
  NumericTablePtr mergedData(new MergedNumericTable(trainData, trainDependentVariables));
#endif

#if 0
  trainDataSource.loadDataBlock();
#else
    trainDataSource.loadDataBlock();
#endif
  NumericTablePtr table = trainDataSource.getNumericTable();
  std::cout << "The table has [" << table->getNumberOfRows() << "] rows\n";
  std::cout << "The table has [" << table->getNumberOfColumns() << "] columns\n";
  
  return EXIT_SUCCESS;
}
#endif
