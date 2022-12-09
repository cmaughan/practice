#include "common.h"

#include <algorithm>
#include <deque>
#include <mutils/time/profiler.h>
#include <mutils/algorithm/container_utils.h>
#include <numeric>
#include <set>

#include <imgui.h>
#include <glm/glm.hpp>

#include <fmt/format.h>

using namespace std;
using namespace MUtils;

namespace
{
uint32_t part1;
uint32_t part2;
std::ostringstream str;
glm::ivec2 scenicCoord;
size_t width;
size_t height;
} // namespace

class AOC_2022_Day8 : public Object
{
    virtual void RunOnce() override
    {
        const auto input = string_get_integer_grid(file_read(PRACTICE_ROOT "/advent_of_code/2022/inputs/day_8.txt"), "");
        width = input[0].size();
        height = input.size();

        auto search = [&](glm::ivec2 coord, auto step, auto& count) {
            auto start = input[coord.y][coord.x];
            coord += step;
            count = 0;
            while (coord.x >= 0 && coord.x < width && coord.y >= 0 && coord.y < height) {
                count++;
                auto current = input[coord.y][coord.x];
                if (current >= start) {
                    return false; 
                }
                coord += step;
            }
            return true;
        };

        uint32_t currentScenic = 0;
        for (uint32_t y = 1; y < input.size() - 1; y++) {
            for (uint32_t x = 1; x < input[y].size() - 1; x++) {
                uint32_t scenic = 1;
                glm::ivec2 coord(x, y);
                bool found = false;
                for (auto& s : { glm::ivec2(0, 1), glm::ivec2(1, 0), glm::ivec2(-1, 0), glm::ivec2(0, -1)}) {
                    uint32_t count;
                    if (search(coord, s, count) && !found) {
                        found = true; 
                        part1++;
                        str << input[coord.y][coord.x];
                    }
                    scenic *= count;
                }
                if (!found) {
                    str << " ";
                }
                if (scenic > currentScenic) {
                    scenicCoord = coord;
                    currentScenic = scenic;
                }
            }
        }
        part1 += uint32_t(width + height + width + height - 4);
        part2 = currentScenic;
    }

    virtual void DrawGUI() override
    {
        PROFILE_SCOPE(ResultPlot);
        if (ImGui::Begin(GetName().c_str()))
        {
            ImGui::Text(fmt::format("Part1: {}", part1).c_str());
            ImGui::Text(fmt::format("Part2: {}", part2).c_str());

            auto out = str.str();
            out[(scenicCoord.y * (width - 2)) + scenicCoord.x] = 'T';
            ImVec2 spriteSize = ImVec2(18, 18);
            float circleSize = 9.0f;
            float circleSizeA = 8.0f;
            auto pDraw = ImGui::GetWindowDrawList();
            ImVec2 offset = ImVec2(200, 250);
            for (uint32_t y = 0; y < (height - 2); y++)
            {
                for (uint32_t x = 0; x < (width - 2); x++)
                {
                    auto val = out[y * (width - 2) + x];
                    if (std::isdigit(val))
                    {
                        uint32_t alpha = uint32_t((255.0f / 9.0f) * (float)(val + 1));
                        //pDraw->AddRectFilled(ImVec2(x * spriteSize.x, y * spriteSize.y),
                         //   ImVec2(x * spriteSize.x + spriteSize.x, y * spriteSize.y + spriteSize.y), 0xFFFFFFFF);
                        pDraw->AddCircleFilled(ImVec2(x * spriteSize.x + circleSize + offset.x, y * spriteSize.y + circleSize + offset.y),
                            circleSizeA, 0x003333DD | (alpha << 24));
                    }
                    else if (val == 'T')
                    {
                        pDraw->AddCircleFilled(ImVec2(x * spriteSize.x + circleSize + offset.x, y * spriteSize.y + circleSize + offset.y),
                            circleSizeA, 0xFF00FF00);
                    }
                }
            }
            //ImGui::TextUnformatted(out.c_str());
        }
        ImGui::End();
    }
};

REGISTER_PROBLEM(AOC_2022_Day8);
