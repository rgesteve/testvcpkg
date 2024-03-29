// define one (and *exactly one*) of the following
#undef SUM_INTEGERS
#undef DAL_TEST
#define ARROW_TEST

#include <filesystem>
#include <iostream>
#include <optional>
#include <rapidcsv.h>
#if 0
#include <xgboost/c_api.h>
#endif

#include "sum_integers.hpp"

#define MAX_ROWS 100

#if 0
std::optional<std::filesystem::path> get_full_path(const std::string& fileName)
{
  auto dataset_path_name = std::getenv("DATASET_PATH");
  if (dataset_path_name == NULL) {
    std::cerr << "Need DATASET_PATH variable defined, couldn't find\n";
    return std::nullopt;
  }
  auto dataset_path = std::filesystem::path(dataset_path_name);
  if (!std::filesystem::exists(dataset_path)) {
    std::cerr << "Cannot find specified path for dataset (" << dataset_path << ")\n";
    return std::nullopt;
  }

  if (!std::filesystem::exists(dataset_path / fileName)) {
    std::cerr << "Cannot find expected file on the path specified (" << dataset_path << ")\n";
    return std::nullopt;
  }

  auto dataset_full_path = dataset_path / fileName;
  return dataset_full_path;
}
#endif

#ifdef SUM_INTEGERS
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

  cout << "******************* main 1" << endl;

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
#endif

#ifdef DAL_TEST
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

   cout << "******************* main 2" << endl;

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
#if 0
  FileDataSource<CSVFeatureManager> trainDataSource(dataset_full_path.string(), DataSource::doAllocateNumericTable, DataSource::doDictionaryFromContext);
#else
  CsvDataSourceOptions csvOptions(CsvDataSourceOptions::allocateNumericTable | CsvDataSourceOptions::createDictionaryFromContext | CsvDataSourceOptions::parseHeader);
  FileDataSource<CSVFeatureManager> trainDataSource(dataset_full_path.string(), csvOptions);
#endif

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

  trainDataSource.loadDataBlock(mergedData.get());

  //NumericTablePtr table = trainDataSource.getNumericTable();
  NumericTablePtr table = mergedData;
  size_t nRows = table->getNumberOfRows();
  size_t nCols = table->getNumberOfColumns();
  std::cout << "The table has [" << nRows << "] rows\n";
  std::cout << "The table has [" << nCols << "] columns\n";
  //  std::cout << "The table is stored in [" << (table->getDataLayout() ) << "] layout\n";
  BlockDescriptor<> block;
  table->getBlockOfRows(0, nRows, readOnly, block);
  DAAL_DATA_TYPE* data = block.getBlockPtr();

  for (size_t i = 0; i < /* nRows*/ 20; i++) {
    for (size_t j = 0; j < nCols; j++) {
      std::cout << data[i * nCols + j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  table->releaseBlockOfRows(block);
  std::cout << "Done!!" << endl;
  
  return EXIT_SUCCESS;
}
#endif

#ifdef ARROW_TEST
#include <iostream>
#include <string>
#include <cstdlib>

#include <arrow/api.h>
#include <arrow/io/api.h>
#include <arrow/csv/api.h>

using namespace std;

int main(int argc, char* argv[])
{
  cout << "******************* main 3" << endl;

  std::cout << "Declaring an array" << std::endl;
  std::array<float, 5> c; //
  std::cout << "Array c is of size " << c.size() << " elements." << std::endl;

  //  const string trainDatasetFilename { "titanic_train.csv" };
  const string trainDatasetFilename { "boston_housing.csv" };

  auto fullPath = get_full_path(trainDatasetFilename);
  if (fullPath.has_value()) {
    cout << "Got a value for the full path" << "\n";
  } else {
    cout << "An error trying out getting a full path for file" << "\n";
    return EXIT_FAILURE;
  }

#if 0
  cout << "Getting the build information on linked XGBoost\n";
  char const* out;
  XGBuildInfo(&out);
  cout << "Using XGBoost with info: [" << out << "]\n" << "\n";

  cout << "Trying to parse file!\n"; 

  // https://github.com/d99kris/rapidcsv/blob/master/doc/rapidcsv_Document.md
  rapidcsv::Document dataset{fullPath.value(),
    rapidcsv::LabelParams{},
    rapidcsv::SeparatorParams{},  
    rapidcsv::ConverterParams{true}
  };

  auto rows = dataset.GetRowCount(); // seems like it skips header
  auto cols = dataset.GetColumnCount(); // seems like it skips header
  auto num_features = cols - 1;
#ifdef MAX_ROWS
  size_t max_rows = MAX_ROWS;
#else
  size_t max_rows = rows;
#endif
  cout << "The document has " << rows << " lines, with " << cols << " fields per line\n";
  cout << "Going to populate an array with " << max_rows << " rows (of " << num_features << " elements each\n";
  #if 0
  float* arr = new float[ max_rows * num_features ];
  float* labels = new float[ max_rows ];
  #else
  // try initializer syntax
  float* arr{new float[ max_rows * num_features ]{}};
  float* labels{new float[ max_rows ]{}};
  #endif
  for (size_t i = 0; i < max_rows; ++i) {
    const auto row = dataset.GetRow<float>(i);
    std::copy(row.begin(), row.end() - 1, arr + (i * num_features));
    labels[i] = row[ num_features ]; // the last field
    cout << "Row " << i << " has " << row.size() << " fields, the first three of which are "
	 << row[0] << ", "
      	 << row[1] << ", "
      	 << row[2] << ", "
	 << " and the last " << row[ row.size() - 1 ] << ".\n";
  }

#ifdef MAX_ROWS
  // Don't output results unless number of rows is capped
  cout << "The arrays that were copied" << endl;
  std::ostream_iterator<float> out_it (std::cout, ", ");
  cout << "Features: " << endl;
  std::copy ( arr, arr + (max_rows * num_features), out_it );
  cout << endl << "Labels: " << endl;
  std::copy ( labels, labels + max_rows, out_it );
#endif

  cout << endl << "Fitting a gradient-boosted model" << endl;
  cout << endl << "Creating matrix with " << max_rows << " rows and " << num_features << " columns." << endl;
  DMatrixHandle dtrain[1];
  XGDMatrixCreateFromMat(arr, max_rows, num_features, -1, &dtrain[0]);

  int ret = XGDMatrixSetFloatInfo(dtrain[0], "label", labels, max_rows);
  if (ret == -1) {
    const char* error_text = XGBGetLastError();
    cerr << "Something happened: [" << error_text << "]" << endl;
  }
  cout << "Was able to assign labels to train matrix" << endl;
  BoosterHandle booster;
  XGBoosterCreate(dtrain, 1, &booster);
  XGBoosterSetParam(booster, "booster", "gbtree");
  XGBoosterSetParam(booster, "objective", "reg:squarederror");
  XGBoosterSetParam(booster, "max_depth", "1");
  XGBoosterSetParam(booster, "base_score", "0");
  // XGBoosterSetParam(booster, "eta", "0.1");
  // XGBoosterSetParam(booster, "n_estimators", "1"); // this is actually captured by numBoostRound
  // XGBoosterSetParam(booster, "max_depth", "1");

  int numBoostRound = 1;
  for (int i = 0; i < numBoostRound; ++i) {
    cout << "Round " << i << endl;
    XGBoosterUpdateOneIter(booster, i, dtrain[0]);
  }

  bst_ulong num_models = 0;
  char** model_string;
  ret = XGBoosterDumpModelEx(booster, "", 0, "json", &num_models, (const char***) &model_string);
  cout << "I should be dumping the model now, got " << ret << " (as result)  and rest:" << num_models << " models" << endl;
  if (num_models > 0) {
    cout << "Dumping the first model " << model_string[0] << endl;
  }
  cout << "------------------------" << endl;

  bst_ulong config_str_len = 0;
  char* booster_config;
  ret = XGBoosterSaveJsonConfig(booster, &config_str_len, (const char**) &booster_config);
  cout << "I should be dumping the booster config now, got " << ret << " (as result)  and a string of length:" << config_str_len << ", containing <<" << booster_config << ">>" << endl;

  // trying out prediction
  cout << "------------------------" << endl;
  DMatrixHandle dtest;
  // last record of the dataset
  const float values[] = { 0.04741,0.0,11.93,0.0,0.573,6.03,80.8,2.505,1.0,273.0,21.0,396.9,7.88  };
  ret = XGDMatrixCreateFromMat(values, 1, 13, 0.0, &dtest);

  cout << "Result of creating test matrix: [" << ret << "]" << endl;
  const float* out_result_pred = NULL;
  char const config[] =
      "{\"training\": false, \"type\": 0, "
      "\"iteration_begin\": 0, \"iteration_end\": 0, \"strict_shape\": false}";
  /* Shape of output prediction */
  uint64_t const* out_shape;
  /* Dimension of output prediction */
  uint64_t out_dim;
  /* Pointer to a thread local contigious array, assigned in prediction function. */
  float const* out_result = NULL;
  ret = XGBoosterPredictFromDMatrix(booster, dtest, config, &out_shape, &out_dim, &out_result_pred);
  cout << "Result of submitting to prediction: [" << ret << "]" << endl;
  if (ret != -1) {
    cout << "Dimensionality of result: [" << out_dim << "]" << endl;
    cout << "Shape of output: [" << out_shape[out_dim - 1] << "]" << endl;
    cout << "Result: [" << out_result_pred[0] << "]" << endl;
  }

  XGDMatrixFree(dtrain[0]);
  XGDMatrixFree(dtest);
  
  delete[] arr;
  delete[] labels;
#endif
  
  return EXIT_SUCCESS;
}
#endif
