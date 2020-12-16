#include "common.h"

#include <algorithm>
#include <numeric>
#include <mutils/time/profiler.h>

#include <imgui.h>
#include <implot.h>

#include <fmt/format.h>

using namespace std;
using namespace MUtils;

namespace
{
    std::string part1;
    std::string part2;
    std::vector<int> input;
    std::vector<int> error;
    std::vector<int> xAxis;
    float minErr = std::numeric_limits<float>::max();
    float maxErr = std::numeric_limits<float>::min();
}

class AOC_2020_Day1 : public Object
{
    virtual void RunOnce() override
    {
        PROFILE_SCOPE(Solution)

            input = string_get_integers(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_1.txt"));

        error.resize(input.size() * input.size());
        xAxis.resize(input.size() * input.size());
        std::iota(xAxis.begin(), xAxis.end(), 0);

        int count = 0;
        container_test_pairs(input, [&](auto a, auto b)
        {
            auto dev = std::abs(2020 - (a + b));
            minErr = std::min(minErr, float(dev));
            maxErr = std::max(maxErr, float(dev));
            error[count++] = dev;

            if ((a + b) == 2020) {
                part1 = std::to_string(a * b);
                return false;
            }
            return true;
        });
        error.resize(count);

        container_test_triples(input, [&](auto a, auto b, auto c)
        {
            if ((a + b + c) == 2020) {
                part2 = std::to_string(a * b * c);
                return false;
            }
            return true;
        });
    }

    virtual void DrawGUI() override
    {
        PROFILE_SCOPE(ResultPlot);
        if (ImGui::Begin("Results"))
        {
            if (xAxis.size() != 0)
            {
                ImPlot::SetNextPlotLimits(0.0f, xAxis[xAxis.size() - 1], minErr, maxErr);
                if (ImPlot::BeginPlot("Deviation",
                    "Index",
                    "Value", ImVec2(-1, 1024)))
                {
                    ImPlot::PlotScatter("Error", xAxis.data(), error.data(), int(error.size()));

                    ImPlot::EndPlot();
                }
                ImGui::Text(fmt::format("Part1: {}", part1).c_str());
                ImGui::Text(fmt::format("Part2: {}", part2).c_str());
            }
        }
        ImGui::End();
    }
};

REGISTER_PROBLEM(AOC_2020_Day1);

