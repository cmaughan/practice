#include "common.h"

#include <algorithm>
#include <deque>
#include <mutils/time/profiler.h>
#include <numeric>
#include <unordered_set>

#include <imgui.h>

#include <fmt/format.h>

using namespace std;
using namespace MUtils;

namespace
{
uint32_t part1;
uint32_t part2;
} // namespace

class AOC_2022_Day6 : public Object
{
    virtual void RunOnce() override
    {
        PROFILE_SCOPE(Solution);
        auto input = file_read(PRACTICE_ROOT "/advent_of_code/2022/inputs/day_6.txt");
        auto findMarkerCount = [&](auto count) {
            for (int i = 0; i < input.size(); i++)
            {
                if (std::unordered_set<char>{ &input[i], &input[i + count] }.size() == count)
                {
                    return i + count;
                }
            }
            return 0;
        };

        part1 = findMarkerCount(4);
        part2 = findMarkerCount(14);
    }

    virtual void DrawGUI() override
    {
        PROFILE_SCOPE(ResultPlot);
        if (ImGui::Begin(GetName().c_str()))
        {
            ImGui::Text(fmt::format("Part1: {}", part1).c_str());
            ImGui::Text(fmt::format("Part2: {}", part2).c_str());
        }
        ImGui::End();
    }
};

REGISTER_PROBLEM(AOC_2022_Day6);
