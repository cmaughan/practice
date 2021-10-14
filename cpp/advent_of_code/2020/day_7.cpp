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
REGISTER_PROBLEM(AOC_2020_Day7)
{
    PROFILE_SCOPE(Solution);

    std::vector<std::string> lines;
    auto in = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_7.txt"));

    std::map<std::string, std::set<std::pair<std::string, int>>> bagMap;
    std::map<std::string, std::set<std::string>> parentBags;
    for (auto& line : in)
    {
        auto tokens = string_split(line, ",. ");
        auto bag = tokens[0] + tokens[1];

        auto current = tokens.begin() + 4;
        while (current != tokens.end())
        {
            auto count_str = *current++;
            if (count_str == "no")
            {
                break;
            }

            auto count = std::stoi(count_str);
            auto inner_bag = *current++;
            inner_bag += *current++;
            current++;
            bagMap[bag].insert(std::make_pair(inner_bag, count));
            parentBags[inner_bag].insert(bag);
        }
    }

    std::set<std::string> foundParents;
    std::function<void(const std::string& bag)> fnSearch;
    fnSearch = [&](const std::string& bag)
    {
        for (auto& parent : parentBags[bag])
        {
            foundParents.insert(parent);
            fnSearch(parent);
        }
    };
    fnSearch("shinygold");
    auto part1 = std::to_string(foundParents.size());

    std::function<int(const std::string& bag)> fnSearchChildren;
    fnSearchChildren = [&](const std::string& bag)
    {
        int count = 1;
        for (auto& [child, childCount] : bagMap[bag])
        {
            count += childCount * fnSearchChildren(child);
        }
        return count;
    };

    int count2 = fnSearchChildren("shinygold") - 1;
    auto part2 = std::to_string(count2);


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


