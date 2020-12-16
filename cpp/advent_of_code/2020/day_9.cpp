#include "common.h"

#include <algorithm>
#include <fstream>
#include <numeric>
#include <regex>
#include <set>
#include <mutils/time/profiler.h>
#include <mutils/math/math.h>
#include <mutils/logger/logger.h>
#include <mutils/string/string_utils.h>

#include <imgui.h>
#include <implot.h>

#include <map>
#include <set>
#include <fmt/format.h>

using namespace std;
using namespace MUtils;

namespace
{
    std::string part1;
    std::string part2;

    class Once
    {
    public:
        Once(std::function<void()> fn)
        {
            fn();
        }
    };
};

#define BEGIN_ONCE static Once once([]()
#define END_ONCE ); 

/*
REGISTER_PROBLEM(AOC_2020_Day9)
{
    PROFILE_SCOPE(Solution);

    std::vector<std::string> lines;
    auto in = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_9.txt"));

    std::vector<uint64_t> vals;
    for (int64_t i = 0; i < int64_t(in.size()); i++)
    {
        auto v = std::stoull(in[i]);
        vals.push_back(v);
    }

    for (int current = 0; current < vals.size(); current++)
    {
        if (current >= 25)
        {
            bool found = false;
            for (int i = 0; i < vals.size(); i++)
            {
                for (int y = 0; y < vals.size(); y++)
                {
                    if (i != y)
                    {
                        if ((vals[i] + vals[y]) == vals[current])
                        {
                            found = true;
                            break;
                        }
                    }
                }
            }
            if (!found)
            {
                part1 = std::to_string(vals[current]);
                break;
            }
        }
    }
    
    uint64_t search = 373803594;
    for (int current = 0; current < vals.size(); current++)
    {
        uint64_t tot = 0;
        uint64_t large = std::numeric_limits<uint64_t>::min();
        uint64_t small = std::numeric_limits<uint64_t>::max();
        for (int acc = current; acc < vals.size(); acc++)
        {
            tot += vals[acc];
            large = std::max(large, vals[acc]);
            small = std::min(small, vals[acc]);
            if (tot > search)
                break;

            if (tot == search && (acc > current))
            {
                part2 = std::to_string(large + small);
                break;
            }
        }
        if (!part2.empty())
            break;
    }

    PROFILE_SCOPE(ResultPlot);
    if (ImGui::Begin("Results"))
    {
        ImGui::Text(fmt::format("Part1: {}", part1).c_str());
        ImGui::Text(fmt::format("Part2: {}", part2).c_str());
    }
    ImGui::End();

    static int resetCount = 2;
    if (resetCount == 0)
    {
        Profiler::SetPaused(true);
    }
    resetCount--;
}
*/


