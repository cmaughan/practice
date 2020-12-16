#include "common.h"

#include <algorithm>
#include <numeric>
#include <mutils/time/profiler.h>
#include <mutils/math/math.h>
#include <mutils/logger/logger.h>

#include <imgui.h>
#include <implot.h>

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

/*
REGISTER_PROBLEM(AOC_2020_Day3)
{
    BEGIN_ONCE
    {
        PROFILE_SCOPE(Solution);
        std::vector<std::string> lines;
        string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_3.txt"), lines);

        auto width = lines[0].size();

        auto countTrees = [&](const auto& step) {
            uint64_t count = 0;
            auto pos = step;
            while (pos.y < lines.size())
            {
                if (lines[pos.y][pos.x % width] == '#')
                    count++;
                pos += step;
            }
            return count;
        };

        auto trees = countTrees(NVec2i(3, 1));
        part1 = std::to_string(trees);

        std::vector<NVec2i> visits{ NVec2i(1, 1), NVec2i(5, 1), NVec2i(7, 1), NVec2i(1, 2) };
        trees = std::accumulate(visits.begin(), visits.end(), trees, [=](auto total, auto& v) {
            return total * countTrees(v);
        });
        part2 = std::to_string(trees);


    } END_ONCE;


    {
        PROFILE_SCOPE(ResultPlot);
        if (ImGui::Begin("Results"))
        {
            ImGui::Text(fmt::format("Part1: {}", part1).c_str());
            ImGui::Text(fmt::format("Part2: {}", part2).c_str());
        }
        ImGui::End();
    }

    static int resetCount = 2;
    if (resetCount == 0)
    {
        Profiler::SetPaused(true);
    }
    resetCount--;
}
*/


