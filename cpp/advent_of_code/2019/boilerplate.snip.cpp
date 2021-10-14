#include "common.h"
#include "mutils/file/file.h"
#include "mutils/string/stringutils.h"
#include "mutils/algorithm/containerutils.h"

#include <algorithm>
#include <numeric>
#include <functional>
#include <set>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include "glm/gtx/hash.hpp"

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2019_DayX)
{
    auto in = string_get_string_grid(file_read(PRACTICE_ROOT "/advent_of_code/2019/inputs/day_X.txt"));
    LOG(INFO) << "Part 1: " << 1;
    LOG(INFO) << "Part 2: " << 2;
}

