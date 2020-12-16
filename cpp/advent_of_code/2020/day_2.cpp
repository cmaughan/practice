#include "common.h"

#include <algorithm>
#include <numeric>
#include <mutils/time/profiler.h>
#include <mutils/math/math.h>

#include <imgui.h>
#include <implot.h>

#include <fmt/format.h>

using namespace std;
using namespace MUtils;

/*
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

REGISTER_PROBLEM(AOC_2020_Day2)
{
    BEGIN_ONCE
    {
        PROFILE_SCOPE(Solution);
            auto lines = string_get_string_grid(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_2.txt"));

    {
        PROFILE_SCOPE(Part1);
        int valid = 0;
        for (auto& line : lines)
        {
            NVec2i range;
            auto ranges = string_split(line[0], "-");
            range.x = std::stoi(ranges[0]);
            range.y = std::stoi(ranges[1]);
            auto matches = std::count_if(line[2].begin(), line[2].end(), [=](auto& ch) {return line[1][0] == ch; });
            if (matches >= range.x && matches <= range.y)
            {
                valid++;
            }
        }
        part1 = std::to_string(valid);
    }

    {
        PROFILE_SCOPE(Part2);

            int valid = 0;
        for (auto& line : lines)
        {
            NVec2i range;
            auto ranges = string_split(line[0], "-");
            range.x = std::stoi(ranges[0]) - 1;
            range.y = std::stoi(ranges[1]) - 1;
            auto match = line[1][0];
            int matches = 0;
            for (int index = 0; index < line[2].size(); index++)
            {
                auto ch = line[2][index];
                if ((ch == match) && ((index == range.x) || (index == range.y)))
                {
                    matches++;
                }
            }
            if (matches == 1)
            {
                valid++;
            }
        }
        part2 = std::to_string(valid);
    }

    } END_ONCE;


    {
        PROFILE_SCOPE(ResultPlot);
        if (ImGui::Begin("Results"))
        {
            ImGui::Text(fmt::format("Part1: {}", part1).c_str());
            ImGui::Text(fmt::format("Part2: {}", part2).c_str());
        }
        ImGui::End();
    }

    static int resetCount = 2;
    if (resetCount == 0)
    {
        Profiler::SetPaused(true);
    }
    resetCount--;
}
*/

