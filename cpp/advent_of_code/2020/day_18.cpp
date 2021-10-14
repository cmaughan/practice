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

#include <unordered_map>
#include <set>
#include <fmt/format.h>

using namespace std;
using namespace MUtils;

class AOC_2020_Day18 : public Object
{
public:
    uint64_t part1;
    uint64_t part2;

    std::vector<std::string> lines;
    virtual void Read()
    {
        lines = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_18.txt"));
        //in = string_split_lines(str);
    }

    virtual void RunOnce() override
    {
        Read();

        for (auto& line : lines)
        {
            string_split(line, " ");
        }
    }

    virtual void DrawGUI() override
    {
        PROFILE_SCOPE(GUI);
        if (ImGui::Begin("Results"))
        {
            ImGui::Text(fmt::format("Part1: {}", part1).c_str());
            ImGui::Text(fmt::format("Part2: {}", part2).c_str());
            ImGui::End();
        }
    }
};


REGISTER_PROBLEM(AOC_2020_Day18)
