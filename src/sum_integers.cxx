#include "sum_integers.hpp"

//#include <vector>

int sum_integers(const std::vector<int> integers) {
  auto sum = 0;
  for (auto i : integers) {
    sum += i;
  }
  return sum;
}

std::optional<std::filesystem::path> get_full_path(const std::string& fileName)
{
  auto dataset_path_name = std::getenv("DATASET_PATH");
  if (dataset_path_name == NULL) {
#ifdef DEBUGGING
    std::cerr << "Need DATASET_PATH variable defined, couldn't find\n";
#endif
    return std::nullopt;
  }
  auto dataset_path = std::filesystem::path(dataset_path_name);
  if (!std::filesystem::exists(dataset_path)) {
#ifdef DEBUGGING
    std::cerr << "Cannot find specified path for dataset (" << dataset_path << ")\n";
#endif
    return std::nullopt;
  }

  if (!std::filesystem::exists(dataset_path / fileName)) {
#ifdef DEBUGGING
    std::cerr << "Cannot find expected file on the path specified (" << dataset_path << ")\n";
#endif
    return std::nullopt;
  }

  auto dataset_full_path = dataset_path / fileName;
  return dataset_full_path;
}
