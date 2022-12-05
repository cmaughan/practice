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

class AOC_2022_Day3 : public Object
{
    virtual void RunOnce() override
    {
        PROFILE_SCOPE(Solution);
        auto rows = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2022/inputs/day_3.txt"));

        auto toScore = [](int v) { return v < 'a' ? ((v - 'A') + 27) : ((v - 'a') + 1); };

        auto search = [&](auto itr, auto itrEnd, auto count) {
            std::vector<std::unordered_set<char>> sets;
            for (auto i = itr; i < itr + count; i++)
            {
                sets.push_back({ (*i).begin(), (*i).end() });
            }

            for (auto& c : *itr)
            {
                if (std::all_of(sets.begin(), sets.end(), [&](auto& s) { return s.contains(c); }))
                    return c;
            }
            return char(0);
        };

        // Make pairs for part 1
        std::vector<std::string> pairs;
        for (auto& row : rows)
        {
            pairs.push_back(row.substr(0, row.length() / 2));
            pairs.push_back(row.substr(row.length() / 2));
        }

        for (auto itr = pairs.begin(); itr != pairs.end(); itr += 2)
        {
            part1 += toScore(search(itr, 2));
        };

        // Triples for part 2
        for (auto itr = rows.begin(); itr != rows.end(); itr += 3)
        {
            part2 += toScore(search(itr, 3));
        };
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

REGISTER_PROBLEM(AOC_2022_Day3);
