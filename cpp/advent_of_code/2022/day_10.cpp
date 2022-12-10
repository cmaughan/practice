#include "common.h"

#include <algorithm>
#include <deque>
#include <glm/ext.hpp>
#include <mutils/algorithm/container_utils.h>
#include <mutils/time/profiler.h>
#include <mutils/time/timer.h>
#include <numeric>
#include <unordered_set>

#include <glm/gtx/hash.hpp>
#include <imgui.h>

#include <fmt/format.h>

using namespace std;
using namespace MUtils;

namespace
{
uint32_t part1;
uint32_t part2;
} // namespace

class AOC_2022_Day10 : public Object
{
    virtual void RunOnce() override
    {
        std::string in = R"(R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2)";

        auto input = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2022/inputs/day_10.txt"));
    }

    virtual void DrawGUI() override
    {
        if (ImGui::Begin(GetName().c_str()))
        {
            ImGui::Text(fmt::format("Part1: {}", part1).c_str());
            ImGui::Text(fmt::format("Part2: {}", part2).c_str());
        }
        ImGui::End();
    }
};

REGISTER_PROBLEM(AOC_2022_Day10);
