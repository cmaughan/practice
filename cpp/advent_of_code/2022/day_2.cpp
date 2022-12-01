#include "common.h"

#include <algorithm>
#include <numeric>
#include <mutils/time/profiler.h>

#include <imgui.h>

#include <fmt/format.h>

using namespace std;
using namespace MUtils;

namespace
{
    int part1;
    int part2;
}

class AOC_2022_Day2 : public Object
{
    virtual void RunOnce() override
    {
        PROFILE_SCOPE(Solution)

        std::vector<int> calories;
        auto elves = string_split_delim_string(file_read(PRACTICE_ROOT "/advent_of_code/2022/inputs/day_1.txt"), "\n\n");
        for (auto& line : elves)
        {
            auto elf = string_get_integers(line);
            auto cal = std::accumulate(elf.begin(), elf.end(), 0);
            calories.push_back(cal);
        }
        std::sort(calories.begin(), calories.end());

        part1 = calories.back();
        part2 = std::accumulate(calories.end() - 3, calories.end(), 0);
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

REGISTER_PROBLEM(AOC_2022_Day2);

