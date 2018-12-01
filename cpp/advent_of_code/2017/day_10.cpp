#include "common.h"
#include "utils.h"
#include "fileutils.h"
#include "stringutils.h"
#include "ringitr.h"

#include <cassert>
#include <limits>
#include <algorithm>
#include <numeric>
using namespace std;

REGISTER_PROBLEM(AOC_2017_Day10)
{
    using ringItrInt = RingIterator<int, std::vector<int>>;

    auto input = std::vector<int>{ 102, 255, 99, 252, 200, 24, 219, 57, 103, 2, 226, 254, 1, 0, 69, 216 };
    input.insert(input.end(), { 17, 31, 73, 47, 23 });

    std::vector<int> key(256);
    std::iota(key.begin(), key.end(), 0);

    auto hash = [&]() {
        int skip_size = 0;
        auto itr = ringItrInt(key);
        for (auto step : input)
        {
            auto itrEnd = ringItrInt(itr) + step;
            std::reverse(itr, itrEnd);
            itr = itrEnd + skip_size;
            skip_size++;
        }
    };


    //auto res1 = hash();
    //LOG(INFO) << "Part 1: " << res1[0] * res1[1];
    //LOG(INFO) << "Part 2: " << garbage_count;
}
