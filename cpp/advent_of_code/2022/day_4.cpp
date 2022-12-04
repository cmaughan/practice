#include "common.h"

#include <algorithm>
#include <mutils/time/profiler.h>
#include <numeric>
#include <unordered_set>

#include <imgui.h>

#include <fmt/format.h>

using namespace std;
using namespace MUtils;

namespace
{
int part1;
int part2;
} // namespace

class AOC_2022_Day4 : public Object
{
    virtual void RunOnce() override
    {
        PROFILE_SCOPE(Solution);
        auto rows = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2022/inputs/day_4.txt"));

        auto a_in_b = [](std::pair<int, int>& a, std::pair<int, int>& b) {
            return (a.first >= b.first && a.second <= b.second)
        };

        auto a_overlap_b = [](std::pair<int, int>& a, std::pair<int, int>& b) {
            return (a.first <= b.second && a.second >= b.first)
        };

        for (auto& row : rows)
        {
            std::pair<int, int> a;
            std::pair<int, int> b;
            sscanf(row.c_str(),"%i-%i,%i-%i", &a.first, &a.second, &b.first, &b.second);
            if (a_in_b(a, b) || a_in_b(b, a))
                part1++;
            if (a_overlap_b(a, b))
                part2++;
        }
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

REGISTER_PROBLEM(AOC_2022_Day4);
