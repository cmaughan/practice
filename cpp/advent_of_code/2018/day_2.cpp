#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"

#include <set>
#include <numeric>

#include "ringitr.h"

using namespace std;
using namespace MUtils;

using IntItr = RingIterator<int, std::vector<int>>;

REGISTER_PROBLEM(AOC_2018_Day2)
{
    auto input = string_split(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_2.txt"));

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
            if (entry.second == 2 && !found2)
            {
                found2 = true;
                num_twos++;
            }
            if (entry.second == 3 && !found3)
            {
                found3 = true;
                num_threes++;
            }
        }
    }
    LOG(INFO) << "Part 1: " << num_twos * num_threes;

    for (auto& s1 : input)
    {
        for (auto& s2 : input)
        {
            // Return number of diffs and build string at the same time without the diffs!
            if (1 == std::inner_product(s1.begin(), s1.end(), s2.begin(), 0, std::plus<>(), [](auto c1, auto c2)
            {
                return (c1 == c2) ? 0 : 1;
            }))
            {
                std::ostringstream str;
                auto diff = std::inner_product(s1.begin(), s1.end(), s2.begin(), 0, std::plus<>(), [&str](auto c1, auto c2)
                {
                    if (c1 == c2)
                    {
                        str << c1;
                    }
                    return 0;
                });

                LOG(INFO) << "Part 2: " << str.str();
                return;
            };
        }
    }
}
