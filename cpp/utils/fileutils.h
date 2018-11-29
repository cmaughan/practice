#pragma once

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem::v1;

namespace FileUtils
{
std::string ReadFile(const fs::path& fileName);
bool WriteFile(const fs::path& fileName, const void* pData, size_t size);
}

