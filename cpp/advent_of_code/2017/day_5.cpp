#include "common.h"
#include "utils.h"
#include "fileutils.h"

#include <cassert>
#include <string>
#include <set>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2017_Day5)
{
    auto jumps = utils_get_integers(file_read(PRACTICE_ROOT  "/advent_of_code/2017/inputs/p5input.txt"));
    int ic = 0;
    int steps = 0;
    while (ic >= 0 && ic < jumps.size())
    {
        ic = ic + jumps[ic]++;
        steps++;
    }
    LOG(INFO) << "Part 1: " << steps;

    jumps = utils_get_integers(file_read(PRACTICE_ROOT  "/advent_of_code/2017/inputs/p5input.txt"));
    ic = 0;
    steps = 0;
    while (ic >= 0 && ic < jumps.size())
    {
        ic = ic + (jumps[ic] >= 3 ? jumps[ic]-- : jumps[ic]++);
        steps++;
    }
    LOG(INFO) << "Part 2: " << steps;
}
