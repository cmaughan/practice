#include "common.h"

#include <string>
#include <set>
#include <cassert>
#include <fstream>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2017_Day4)
{
    std::ifstream t(fs::path(PRACTICE_ROOT) / "advent_of_code/2017/inputs/p4input.txt");
    assert(t.is_open());
    std::stringstream buffer;
    buffer << t.rdbuf();
    auto p4lines = string_get_string_grid(buffer.str());

    auto FindDuplicates = [p4lines](bool anagrams = false)
    {
        int badCount = 0;
        for (auto& l : p4lines)
        {
            std::set<std::string> entries;
            for (auto w : l)
            {
                if (anagrams)
                    std::sort(w.begin(), w.end());

                if (entries.find(w) != entries.end())
                {
                    badCount++;
                    break;
                }
                entries.insert(w);
            }
        }
        return int(p4lines.size()) - badCount;
    };
    LOG(INFO, "P4,1" << FindDuplicates());
    LOG(INFO, "P4,2" << FindDuplicates(true));
}
