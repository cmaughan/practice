#include "common.h"

#include <deque>
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
std::string part1;
std::string part2;
} // namespace

class AOC_2022_Day5 : public Object
{
    virtual void RunOnce() override
    {
        PROFILE_SCOPE(Solution);
        auto rows = string_split_delim_string(file_read(PRACTICE_ROOT "/advent_of_code/2022/inputs/day_5.txt"), "\n\n");
        auto crates = string_split_lines(string_split(rows[0], "1")[0]);
        std::reverse(crates.begin(), crates.end());

        std::vector<std::deque<char>> stacks[2];

        stacks[0].resize(9);
        for (auto crate_row : crates)
        {
            int stack = 0;
            for (int index = 1; index < crate_row.length(); index += 4)
            {
                if (crate_row[index] != ' ')
                {
                    stacks[0][stack].push_back(crate_row[index]);
                }
                stack++;
            }
        }
        stacks[1] = stacks[0];

        auto commands = string_split_lines(rows[1]);
        for (auto& command : commands) 
        {
            int count, from, to;
            sscanf(command.c_str(), "move %i from %i to %i", &count, &from, &to);
            from--;
            to--;
            for (int i = 0; i < count; i++)
            {
                stacks[0][to].push_back(stacks[0][from].back());
                stacks[0][from].pop_back();
            }

            auto end = stacks[1][from].end();
            auto start = end - count;
            for (auto itr = start; itr != end; itr++)
            {
                stacks[1][to].push_back(*itr);
            }
            stacks[1][from].erase(start, end);
        }

        for (auto& stack : stacks[0])
        {
            part1 += stack.back();
        }
        
        for (auto& stack : stacks[1])
        {
            part2 += stack.back();
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

REGISTER_PROBLEM(AOC_2022_Day5);
