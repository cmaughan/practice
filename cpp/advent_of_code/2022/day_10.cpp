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
int64_t part1;
int64_t part2;
std::vector<int64_t> values;
} // namespace

class AOC_2022_Day10 : public Object
{
    virtual void RunOnce() override
    {
        auto input = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2022/inputs/day_10.txt"));
        int64_t x = 1;
        int64_t sig_strength = 0;
        for (auto& line : input)
        {
            int64_t val = 0;
            int count = 1;
            if (line[0] == 'a')
                count = 2;

            for (int i = 0; i < count; i++)
            {
                values.push_back(x);
            }

            if (count == 2)
            {
                x += std::stoi(line.substr(5));
            }
        }

        for (int v = 20; v <= 220; v += 40)
        {
            part1 += values[v - 1] * v;
        }
    }

    virtual void DrawGUI() override
    {
        if (ImGui::Begin(GetName().c_str()))
        {
            ImGui::Text(fmt::format("Part1: {}", part1).c_str());
            ImGui::Text("Part2:");
            float size = 10;
            float offset = 300;

            auto pDraw = ImGui::GetWindowDrawList();
            for (int i = 0; i < values.size() - 1; i++)
            {
                auto x = i % 40;
                auto y = i / 40;
                if (values[i] - 1 <= x && x <= values[i] + 1)
                    pDraw->AddRectFilled(ImVec2((x * size) + offset, (y * size) + offset), ImVec2((x * size) + offset + size, (y * size) + offset + size), 0xFFFFFFFF);
            }
        }
        ImGui::End();
    }
};

REGISTER_PROBLEM(AOC_2022_Day10);
