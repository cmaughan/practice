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



class AOC_2020_Day10 : public Object
{
    std::string part1;
    std::string part2;

    virtual void RunOnce() override
    {
        PROFILE_SCOPE(Solution);

        std::vector<std::string> lines;

        auto in = string_get_integers(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_10.txt"));
        std::sort(in.begin(), in.end());

        // Part 1
        std::vector<int> jolts;
        int current_jolt = 0;
        int one_jolt_diff = 0;
        int three_jolt_diff = 0;
        for (int i = 0; i < in.size(); i++)
        {
            int min = std::numeric_limits<int>::max();
            int max = std::numeric_limits<int>::min();
            for (auto& v : in)
            {
                if (v > (current_jolt + 3))
                    break;
                if (v > current_jolt)
                {
                    min = std::min(v, min);
                    max = std::max(v, max);
                }
            }
            jolts.push_back(min);
            assert(min > current_jolt);
            auto diff = min - current_jolt;
            if (diff == 1)
                one_jolt_diff++;
            else if (diff == 3)
                three_jolt_diff++;
            current_jolt = min;
        }
        part1 = std::to_string(one_jolt_diff * (three_jolt_diff + 1));

        // Part 2
        std::map<uint64_t, uint64_t> results;
        using fnSearch = std::function<uint64_t(uint64_t, uint64_t)>;
        fnSearch search = [&](uint64_t jolt, uint64_t location) -> uint64_t {
            uint64_t count = 0;
            bool found = false;
            for (uint64_t i = location; i < in.size(); i++)
            {
                if (in[i] > (jolt + 3))
                    break;

                found = true;

                if (results.find(in[i]) != results.end())
                {
                    count += results[in[i]];
                }
                else
                {
                    auto ret = search(in[i], i + 1);
                    results[in[i]] = ret;
                    count += ret;
                }
            }
            if (!found)
            {
                return 1;
            }
            return count;
        };

        auto count = search(0, 0);

        part2 = std::to_string(count);
    }

    virtual void DrawGUI() override
    {
        PROFILE_SCOPE(ResultPlot);
        if (ImGui::Begin("Results"))
        {
            ImGui::Text(fmt::format("Part1: {}", part1).c_str());
            ImGui::Text(fmt::format("Part2: {}", part2).c_str());
        }
        ImGui::End();
    }
};

REGISTER_PROBLEM(AOC_2020_Day10)


