#include "common.h"

#include <algorithm>
#include <fstream>
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

/*
REGISTER_PROBLEM(AOC_2020_Day5)
{
    PROFILE_SCOPE(Solution);

    std::vector<std::string> lines;
    auto in = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_5.txt"));

    std::set<int> found;
    int maxId = 0;
    for (auto& line : in)
    {
        NVec2i row(0, 127);
        NVec2i column(0, 7);
        //line = "BFFFBBFRRR";
        for (auto& ch : line)
        {
            int diffRow = ((row.y - row.x) +1) / 2;
            int diffColumn = ((column.y - column.x) + 1) / 2;
            if (ch == 'F')
            {
                row.y = row.y - diffRow;
            }
            else if (ch == 'B')
            {
                row.x = row.x + diffRow;
            }
            else if (ch == 'L')
            {
                column.y = column.y - diffColumn;
            }
            else if (ch == 'R')
            {
                column.x = column.x + diffColumn;
            }
        }
        auto id = row.x * 8 + column.x;
        maxId = std::max(id, maxId);
        found.insert(id);
    }

    for (int i = 0; i < maxId; i++)
    {
        if (found.find(i) == found.end())
        {
            LOG(DBG, "Missing: " << i);
        }
    }

    part1 = std::to_string(maxId);

    PROFILE_SCOPE(ResultPlot);
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


