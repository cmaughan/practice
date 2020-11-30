#include "common.h"

#include <algorithm>
#include <numeric>

#include <imgui.h>

#include <fmt/format.h>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM_GUI(AOC_2020_Day1)

std::string part1;
std::string part2;

void AOC_2020_Day1::Run()
{
    auto input = string_get_integers(file_read(PRACTICE_ROOT "/advent_of_code/2019/inputs/day_1.txt"));

    // Part 1 (mass / 3 rounded down - 2, accumulate)
    part1 = std::to_string(std::accumulate(input.begin(), input.end(), 0,
        [&](int total, int val) {
        return total + ((val / 3) - 2);
    }));


    part2 = std::to_string(std::accumulate(input.begin(), input.end(), 0,
        [&](int total, int val) {

        std::function<int(int)> fnMass = [&](int mass) {
            int ret = ((mass / 3) - 2);
            return (ret <= 0) ? 0 : ret + fnMass(ret);
        };

        return total + fnMass(val);
    }));
}

void AOC_2020_Day1::DrawGUI()
{
    if (ImGui::Begin("Results"))
    {
        ImGui::Text(fmt::format("Part1: {}", part1).c_str());
        ImGui::Text(fmt::format("Part2: {}", part2).c_str());
    }
    ImGui::End();
}

