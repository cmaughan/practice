#include "common.h"

#include <set>

using namespace MUtils;

REGISTER_PROBLEM(AOC_2017_Day6)
{
    using ringItrInt = RingIterator<int, std::vector<int>>;

    auto banks = string_get_integers("10	3	15	10	5	15	5	15	9	2	5	8	5	2	3	6");
    auto banks2 = banks;
    auto FindLoop = [&banks](bool loopSize = false)
    {
        std::set<std::vector<int>> matches;
        for (;;)
        {
            ringItrInt itr(banks, std::max_element(banks.begin(), banks.end()));
            auto count = size_t(*itr);
            *itr = 0;
            std::for_each_n(itr + 1, count, [](int& val) { val++; });
            if (matches.find(banks) != matches.end())
            {
                if (!loopSize)
                {
                    return int(matches.size());
                }
                loopSize = false;
                matches.clear();
            }
            matches.insert(banks);
        }
    };
    LOG(INFO, "Part 1: " << FindLoop(false) + 1);

    banks = banks2;
    LOG(INFO, "Part 2: " << FindLoop(true));
}
