#include "common.h"
#include "mutils/file/file.h"
#include "mutils/string/stringutils.h"
#include "mutils/algorithm/containerutils.h"

#include <algorithm>
#include <numeric>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2019_Day1)
{
    auto input = string_get_integers(file_read(PRACTICE_ROOT "/advent_of_code/2019/inputs/day_1.txt"));

    // Part 1 (mass / 3 rounded down - 2, accumulate)
    LOG(INFO) << "Part1: " << std::accumulate(input.begin(), input.end(), 0,
        [&](int total, int val) {
        return total + ((val / 3) - 2);
    });


    LOG(INFO) << "Part2: " << std::accumulate(input.begin(), input.end(), 0,
        [&](int total, int val) {
       
        std::function<int(int)> fnMass = [&](int mass) {
            int ret = ((mass / 3) - 2);
            return (ret <= 0) ? 0 : ret + fnMass(ret);
        };

        return total + fnMass(val);
    });
}

