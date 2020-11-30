#include "common.h"
//#include "utils.h"
//#include "fileutils.h"
//#include "stringutils.h"
//#include "ringitr.h"

#include <cassert>
#include <limits>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2017_Day10)
{
    using ringItrInt = RingIterator<int, std::vector<int>>;

    // Implement the hash function for one pass through the shifter inputs
    auto hash = [&](auto& itr, auto& vec, int& skip_size) {
        for (auto step : vec)
        {
            auto itrEnd = ringItrInt(itr) + step;
            std::reverse(itr, itrEnd);
            itr = itrEnd + skip_size;
            skip_size++;
        }
    };

    // First part of the problem uses a list of integers
    auto inputVals = std::vector<int>{ 102, 255, 99, 252, 200, 24, 219, 57, 103, 2, 226, 254, 1, 0, 69, 216 };
    std::vector<int> key(256);
    std::iota(key.begin(), key.end(), 0);
    auto itr = ringItrInt(key);
    int skip_size = 0;
    hash(itr, inputVals, skip_size);
    LOG(INFO, "Part 1: " << key[0] * key[1]);

    // Second part of the problem uses a literal string as a binary input and appends magic numbers
    // Note: A different container type, but the hash function doesn't care!
    auto input = std::string("102,255,99,252,200,24,219,57,103,2,226,254,1,0,69,216");
    input.insert(input.end(), { 17, 31, 73, 47, 23 });
    std::iota(key.begin(), key.end(), 0);

    // Run 64 times
    itr = ringItrInt(key);
    skip_size = 0;
    for (int i = 0; i < 64; i++)
    {
        hash(itr, input, skip_size);
    }

    // Splice the data into chunks of 16 and reduce by xor'ing the values
    std::ostringstream output;
    output << std::setw(2) << std::setfill('0') << std::hex;
    container_splice(key, key.begin(), 16, [&output](auto itr1, auto itr2)
    {
        output << std::reduce(itr1, itr2, 0, [](auto current, auto val)
        {
            return current ^= val;
        });
    });

    LOG(INFO, "Part 2: " << output.str());
}
