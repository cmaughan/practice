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

        enum Kind { Rock = 1, Paper = 2, Scissors = 3 };
        enum Result { Lose = 1, Draw = 2, Win = 3 };
        struct Results { Kind me; Kind opponent; int score; Result result; };
        std::vector<Results> res = {
            { Rock, Rock, Rock + 3, Draw},
            { Rock, Paper, Rock, Lose},
            { Rock, Scissors, Rock + 6, Win},

            { Paper, Rock, Paper + 6, Win},
            { Paper, Paper, Paper + 3, Draw},
            { Paper, Scissors, Paper, Lose},

            { Scissors, Rock, Scissors, Lose},
            { Scissors, Paper, Scissors + 6, Win},
            { Scissors, Scissors, Scissors + 3, Draw}
        };

        const auto rows = string_get_string_grid(file_read(PRACTICE_ROOT "/advent_of_code/2022/inputs/day_2.txt"));
        part1 = part2 = 0;
        for (auto& row : rows)
        {
            auto me = row[1][0] - 'X' + 1;
            auto opponent = row[0][0] - 'A' + 1;
            auto itr = std::find_if(res.begin(), res.end(), [=](auto& val) { return val.me == me && val.opponent == opponent; });
            part1 += itr->score;

            itr = std::find_if(res.begin(), res.end(), [=](auto& val) { return val.result == me && val.opponent == opponent; });
            part2 += itr->score;
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

REGISTER_PROBLEM(AOC_2022_Day2);

