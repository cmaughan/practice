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


/*REGISTER_PROBLEM(AOC_2020_Day6)
{
    PROFILE_SCOPE(Solution);

    std::vector<std::string> lines;
    auto in = string_split_delim_string(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_6.txt"), "\r\n\r\n");

    int total1 = 0;
    int total2 = 0;
    for (auto& group : in)
    {
        struct val { int i = 0; };
        std::map<char, val> counts;
        auto lines = string_split(group, "\r\n");
        for (auto& text : lines)
        {
            for (auto& ch : text)
            {
                counts[ch].i++;
            }
        }

        // Part 1
        total1 += int(counts.size());
       
        // Part 2
        total2 += (int)std::count_if(counts.begin(), counts.end(), [&lines](auto& pair) {
            return pair.second.i == lines.size();
        });
    }

    part1 = std::to_string(total1);
    part2 = std::to_string(total2);

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


