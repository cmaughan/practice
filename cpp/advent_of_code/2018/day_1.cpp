#include "common.h"

#include "fileutils.h"
#include "utils.h"

#include <set>
#include <algorithm>
#include <numeric>

#include "ringitr.h"
using namespace std;

using IntItr = RingIterator<int, std::vector<int>>;

REGISTER_PROBLEM(AOC_2018_Day1)
{
    auto input = utils_get_integers(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_1.txt"));

    // Part 1 (add all digits together)
    LOG(INFO) << "Part1: " << std::accumulate(input.begin(), input.end(), 0, [&](int total, int val) { return total += val; });

    // Part 2
    int result = 0;
    IntItr itr(input);
    std::set<int> visited;
    visited.insert(result);
    for(;;)
    {
        result += *itr++;
        if (visited.find(result) != visited.end())
        {
            LOG(INFO) << "Part2: " << result;
            return;
        }
        visited.insert(result);
    }
}
