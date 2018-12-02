#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"

#include <set>
#include <numeric>

#include "ringitr.h"
using namespace std;

using IntItr = RingIterator<int, std::vector<int>>;

REGISTER_PROBLEM(AOC_2018_Day2)
{
    auto input = string_split(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_2.txt"));

    std::vector<std::string> boxes;
    int num_twos = 0;
    int num_threes = 0;
    for (auto& s : input)
    {
        std::map<char, int> counts;
        for (auto& c : s)
        {
            int count = utils_get_with_default(counts, c, 0);
            counts[c] = count + 1;
        }

        bool found2 = false;
        bool found3 = false;
        for (auto& entry : counts)
        {
            if (entry.second == 2)
                found2 = true;
            if (entry.second == 3)
                found3 = true;
        }
        if (found2)
            num_twos++;
        if (found3)
            num_threes++;
        if (found2 || found3)
        {
            boxes.push_back(s);
        }
    }
    LOG(INFO) << "Part 1: " << num_twos * num_threes;

    int bestCompare = std::numeric_limits<int>::max();
    for (auto& s1 : boxes)
    {
        for (auto& s2 : boxes)
        {
            if (s2 == s1)
                continue;

            // Return number of diffs and build string at the same time without the diffs!
            std::ostringstream str;
            int diffs = std::inner_product(s1.begin(), s1.end(), s2.begin(), 0, std::plus<>(), [&str](auto c1, auto c2)
            {
                if (c1 == c2)
                {
                    str << c1;
                    return 0;
                }
                return 1;
            });

            if (diffs == 1)
            {
                LOG(INFO) << "Part 2: " << str.str();
                return;
            }
        }
    }
}
