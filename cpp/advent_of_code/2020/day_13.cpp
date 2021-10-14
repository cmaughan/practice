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

std::vector<uint64_t> ReadBuses(uint64_t& startTime)
{
    PROFILE_SCOPE(Read);
    auto in = string_split(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_13.txt"), "\r\n, ");
    startTime = std::stoull(in[0]);

    std::vector<uint64_t> buses;
    for (uint32_t index = 1; index < in.size(); index++)
    {
        auto& val = in[index];
        if (val[0] == 'x')
        {
            buses.push_back(1);
        }
        else
        {
            auto id = std::stoull(val);
            buses.push_back(id);
        }
    }
    return buses;
}

uint64_t Part1()
{
    uint64_t startTime;
    auto buses = ReadBuses(startTime);

    PROFILE_SCOPE(Part1);
    uint64_t answer = 0;
    uint64_t time = 0;
    for (;;)
    {
        for (uint32_t busNum = 0; busNum < buses.size(); busNum++)
        {
            if (buses[busNum] != 1 && (time % buses[busNum]) == 0)
            {
                if (time >= startTime)
                {
                    return ((time - startTime) * buses[busNum]);
                }
            }
        }
        time++;
    }
}


uint64_t Part2()
{
    uint64_t startTime;
    auto buses = ReadBuses(startTime);

    PROFILE_SCOPE(Part2);

    std::vector<uint64_t> found;
    found.resize(buses.size(), 0);

    uint64_t time = 0;
    uint64_t startBus = 0;
    uint64_t currentStep = buses[0];
    
    for (uint64_t bus = startBus; bus < buses.size(); bus++)
    {
        // Not the right bus, step time and start again
        if ((time + bus) % buses[bus] != 0)
        {
            time += currentStep;
            bus = startBus;
            continue;
        }
    
        // Found it?
        if (bus == (buses.size() - 1))
        { 
            return time;
        }

        // Not done, so step by the bus increment if we can
        if (found[bus] != 0)
        {
            // How far we step to get to the next bus is our new step
            // This is the step we need to get to a point where all previous buses work
            // This will only ever be a 'greater' step than we needed to do previously, as the 
            // combination becomes more complex.
            auto newStep = time - found[bus];
            if (newStep > currentStep)
            {
                currentStep = newStep;

                // No longer need to consider previous buses
                startBus = bus;
            }
        }
        found[bus] = time;
    }

    return 0;
}

/*
REGISTER_PROBLEM(AOC_2020_Day13)
{
    PROFILE_SCOPE(Solution);

    part1 = std::to_string(Part1());
    part2 = std::to_string(Part2());
    if (ImGui::Begin("Results"))
    {

        ImGui::Text(fmt::format("Part1: {}", part1).c_str());
        ImGui::Text(fmt::format("Part2: {}", part2).c_str());
    }
    ImGui::End();

    static int resetstartTime = 2;
    if (resetstartTime == 0)
    {
        Profiler::SetPaused(true);
    }
    resetstartTime--;
}
*/


