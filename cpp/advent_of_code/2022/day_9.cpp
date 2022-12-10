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
std::vector<glm::ivec2> tails;
std::unordered_set<glm::ivec2> visited;
std::vector<std::string> input;
uint32_t index = 0;
timer t;
float last_time = 0.0f;
size_t num_tails = 9;
glm::ivec2 head;
glm::vec2 lastSize;
glm::ivec2 lastMin;
} // namespace

class AOC_2022_Day9 : public Object
{
    void NextLine(std::string& line)
    {
        glm::ivec2 dir;
        switch (line[0])
        {
        case 'U': dir = glm::ivec2(0, -1); break;
        case 'D': dir = glm::ivec2(0, 1); break;
        case 'L': dir = glm::ivec2(-1, 0); break;
        case 'R': dir = glm::ivec2(1, 0); break;
        }

        auto count = std::stoi(line.substr(2));
        for (int i = 0; i < count; i++)
        {
            head += dir;

            for (uint32_t i = 0; i < num_tails; i++)
            {
                glm::ivec2 target = head - tails[i];
                if (i != 0)
                    target = tails[i-1] - tails[i];
                if (abs(target.x) > 1 || abs(target.y) > 1)
                {
                    if (abs(target.x) > 1)
                        target.x /= 2;
                    if (abs(target.y) > 1)
                        target.y /= 2;
                    tails[i] += target;
                }
                if (i == (num_tails - 1))
                visited.insert(tails[i]);
            }
        }
    }

    virtual void RunOnce() override
    {
        head = glm::ivec2(0, 0);
        visited.insert(glm::ivec2(0, 0));
        for (uint32_t i = 0; i < num_tails; i++)
        {
            tails.push_back(glm::ivec2(0, 0));
        }
        std::string in = R"(R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2)";

        input = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2022/inputs/day_9.txt"));

        last_time = float(timer_get_elapsed_seconds(t) + 1.0);
        lastSize = glm::vec2(10000.0f, 100000.0f);
        lastMin = glm::ivec2(0.0f, 0.0f);
    }

    virtual void DrawGUI() override
    {
        auto elapsed = timer_get_elapsed_seconds(t);
        if (elapsed > (last_time + 0.1f))
        {
            if (index < input.size())
            {
                NextLine(input[index]);
                index++;
            }
            last_time = float(elapsed);
        }
        part1 = (uint32_t)visited.size();

        PROFILE_SCOPE(ResultPlot);
        if (ImGui::Begin(GetName().c_str()))
        {
//            ImGui::Text(fmt::format("Part1: {}", part1).c_str());
//            ImGui::Text(fmt::format("Part2: {}", part2).c_str());

            glm::ivec2 max = glm::ivec2(-999999, -999999);
            glm::ivec2 min = glm::ivec2(9999999, 9999999);
            if (visited.empty())
            {
                ImGui::End();
                return;
            }
            for (auto& v : visited)
            {
                max = glm::ivec2(std::max(v.x, max.x), std::max(v.y, max.y));
                min = glm::ivec2(std::min(v.x, min.x), std::min(v.y, min.y));
            }
            max = glm::ivec2(std::max(head.x, max.x), std::max(head.y, max.y));
            min = glm::ivec2(std::min(head.x, min.x), std::min(head.y, min.y));
            min = glm::min(min, lastMin);
            lastMin = min;

            auto range = abs(max - min);
            if (range.x == 0 || range.y == 0)
            {
                ImGui::End();
                return;
            }

            auto pDraw = ImGui::GetWindowDrawList();
            auto minWin = pDraw->GetClipRectMin();
            minWin.y += 40.0f;
            auto maxWin = pDraw->GetClipRectMax();

            glm::vec2 sz(float(std::min(maxWin.x - minWin.x, maxWin.y - minWin.y))/(std::max(range.x, range.y)));
            sz.x = std::max(1.0f, sz.x);
            sz.y = std::max(1.0f, sz.y);
            sz *= 0.9f;
            sz = glm::min(lastSize, sz);
            lastSize = sz;
            //glm::vec2 sz(10.0f);
            glm::vec2 inset(0.0f, 0.0f);
            glm::vec2 offset = glm::vec2(minWin.x, minWin.y);

            auto draw = [&](auto v, auto col) {
                auto p = (sz * glm::vec2(v - min));
                p += offset;
                //p += offset;
                pDraw->AddCircleFilled(ImVec2(p.x + sz.x * .5f, p.y + sz.y * .5f), (sz.x * .5f) - inset.x, col);// ImVec2(p2.x, p2.y), col);
            };
            for (auto& v : visited)
            {
                draw(v, 0xFFFFFFFF);
            }
            draw(head, 0xFF3333FF);
            for (int i = 0; i < num_tails; i++)
            {
                draw(tails[i], 0xFF22FF22);
            }
            // ImGui::TextUnformatted(out.c_str());
        }
        ImGui::End();
    }
};

REGISTER_PROBLEM(AOC_2022_Day9);
