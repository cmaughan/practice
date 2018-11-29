#include "common.h"
#include "utils.h"
#include "fileutils.h"

#include <cassert>
#include <string>
#include <set>

using namespace std;

REGISTER_PROBLEM(AOC_2017_Day5)
{
    std::ifstream p5file(PRACTICE_ROOT  "/advent_of_code/2017/inputs/p5input.txt");
    assert(p5file.is_open());
    std::vector<int> jumps{ std::istream_iterator<int>{p5file}, {} };
    int ic = 0;
    int steps = 0;
    while (ic >= 0 && ic < jumps.size())
    {
        ic = ic + jumps[ic]++;
        steps++;
    }
    LOG(INFO) << "P5,1" << steps;

    p5file.clear();
    p5file.seekg(0, ios::beg);
    jumps = std::vector<int>{ std::istream_iterator<int>{p5file}, {} };
    ic = 0;
    steps = 0;
    while (ic >= 0 && ic < jumps.size())
    {
        ic = ic + (jumps[ic] >= 3 ? jumps[ic]-- : jumps[ic]++);
        steps++;
    }
    LOG(INFO) << "P5,2" << steps;
}
