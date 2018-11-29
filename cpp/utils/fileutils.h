#pragma once

#include "config_app.h"

#include <istream>
#include <iostream>
#include <iterator>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem::v1;

std::string file_read(const fs::path& fileName);
bool file_write(const fs::path& fileName, const void* pData, size_t size);

