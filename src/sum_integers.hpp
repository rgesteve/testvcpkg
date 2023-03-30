#pragma once

#include <vector>

#include <filesystem>
#include <optional>

int sum_integers(const std::vector<int> integers);
std::optional<std::filesystem::path> get_full_path(const std::string& fileName);
