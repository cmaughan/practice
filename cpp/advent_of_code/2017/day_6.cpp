#include "common.h"
#include "fileutils.h"

#include <set>
#include "ringitr.h"

REGISTER_PROBLEM(AOC_2017_Day6)
{
    using ringItrInt = RingIterator<int, std::vector<int>>;

    std::string input6 = "10	3	15	10	5	15	5	15	9	2	5	8	5	2	3	6";
    auto banks = std::vector<int>{ std::istream_iterator<int>{std::istringstream(input6)}, {} };
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
    LOG(INFO) << "P6,1" << FindLoop(false) + 1;

    banks = std::vector<int>{ std::istream_iterator<int>{std::istringstream(input6)}, {} };
    LOG(INFO) << "P6,1" << FindLoop(true);
}
