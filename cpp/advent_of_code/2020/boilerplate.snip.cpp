#include "common.h"

#include <algorithm>
#include <numeric>
#include <functional>
#include <set>

using namespace std;
using namespace MUtils;


class AOC_2020_DayX : public Object
{
    virtual void Run() override
    {
        auto in = string_get_string_grid(file_read(PRACTICE_ROOT "/advent_of_code/2019/inputs/day_X.txt"));
        LOG(INFO, "Part 1: " << 1);
        LOG(INFO, "Part 2: " << 2);
    }
};

REGISTER_PROBLEM(AOC_2020_DayX);

