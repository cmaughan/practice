#include "common.h"

#include <algorithm>
#include <fstream>
#include <array>
#include <numeric>
#include <regex>
#include <set>
#include <mutils/time/profiler.h>
#include <mutils/math/math.h>
#include <mutils/logger/logger.h>
#include <mutils/string/string_utils.h>

#include <imgui.h>
#include <implot.h>

#include <map>
#include <set>
#include <fmt/format.h>

using namespace std;
using namespace MUtils;

namespace
{
    std::string part1;
    std::string part2;

    class Once
    {
    public:
        Once(std::function<void()> fn)
        {
            fn();
        }
    };
};

#define BEGIN_ONCE static Once once([]()
#define END_ONCE ); 

float Length(NVec2f dir)
{
    float norm = ((dir.x * dir.x) + (dir.y * dir.y));
    return std::sqrt(norm);
}

NVec2f Normalize(NVec2f dir)
{
    float norm = float((dir.x * dir.x) + (dir.y * dir.y));
    norm = std::sqrt(float(norm));
    dir.x = (dir.x / norm);
    dir.y = (dir.y / norm);
    return dir;
};

NVec2f Rotate(const NVec2f& vec, float angle)
{
    const float PI = 3.141598f;
    float radians = angle * (PI / 180.0f);
    NVec2f out;
    out.x = (float(vec.x) * cos(radians) - float(vec.y) * sin(radians));
    out.y = (float(vec.x) * sin(radians) + float(vec.y) * cos(radians));
    return out;
}

NVec2f RotateAroundPoint(NVec2f origin, NVec2f point, float angle)
{
    const float PI = 3.141598f;
    float radians = angle * (PI / 180.0f);

    point -= origin;

    float x = (float(point.x) * cos(radians) - float(point.y) * sin(radians));
    float y = (float(point.x) * sin(radians) + float(point.y) * cos(radians));

    point.x = (x + origin.x);
    point.y = (y + origin.y);
    return point;
}

uint32_t Part1()
{
    std::vector<std::string> lines;
    auto str = R"(
F10
N3
F7
R90
F11
)";

    auto in = string_split(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_12.txt"), " \r\n");

    NVec2f location(0, 0);
    NVec2f forward(1, 0);

    for (auto& command : in)
    {
        auto cmd = command[0];
        auto count = float(std::stoi(command.substr(1)));
        switch (cmd)
        {
        case 'N':
            location += NVec2f(0, count);
            break;
        case 'S':
            location += NVec2f(0, -count);
            break;
        case 'E':
            location += NVec2f(count, 0);
            break;
        case 'W':
            location += NVec2f(-count, 0);
            break;
        case 'R':
            forward = Rotate(forward, -count);
            break;
        case 'L':
            forward = Rotate(forward, count);
            break;
        case 'F':
            location.x += (forward.x * count);
            location.y += (forward.y * count);
            break;
        }

    }

    return int(std::abs(location.x) + std::abs(location.y));

}

uint32_t Part2()
{
    std::vector<std::string> lines;

    auto in = string_split(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_12.txt"), " \r\n");

    NVec2f ship(0, 0);
    NVec2f location(10, 1);

    for (auto& command : in)
    {
        auto cmd = command[0];
        auto count = float(std::stoi(command.substr(1)));

        switch (cmd)
        {
        case 'N':
            location += NVec2f(0, count);
            break;
        case 'S':
            location += NVec2f(0, -count);
            break;
        case 'E':
            location += NVec2f(count, 0);
            break;
        case 'W':
            location += NVec2f(-count, 0);
            break;
        case 'R':
            location = RotateAroundPoint(ship, ship + location, -count) - ship;
            break;
        case 'L':
            location = RotateAroundPoint(ship, ship + location, count) - ship;
            break;
        case 'F':
            ship.x += location.x * count;
            ship.y += location.y * count;
            break;
        }

    }

    return int(std::abs(roundf(ship.x)) + std::abs(roundf(ship.y)));

}

/*
REGISTER_PROBLEM(AOC_2020_Day12)
{
    PROFILE_SCOPE(Solution);
    PROFILE_SCOPE(ResultPlot);

    part1 = std::to_string(Part1());
    part2 = std::to_string(Part2());
    if (ImGui::Begin("Results"))
    {

        ImGui::Text(fmt::format("Part1: {}", part1).c_str());
        ImGui::Text(fmt::format("Part2: {}", part2).c_str());
    }
    ImGui::End();

    static int resetCount = 2;
    if (resetCount == 0)
    {
        Profiler::SetPaused(true);
    }
    resetCount--;
}
*/


