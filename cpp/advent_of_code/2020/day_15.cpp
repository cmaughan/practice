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

class AOC_2020_Day15 : public Object
{
public:
    std::string part1;
    std::string part2;

    uint64_t Parts(int part)
    {
        std::vector<int> lastSpoken;
        lastSpoken.resize(30000001, 0);

        auto numbers = string_get_integers("20,9,11,0,1,2");
        for (int i = 0; i < numbers.size(); i++)
        {
            lastSpoken[numbers[i]] = i + 1;
        }

        int speak;
        int next = 0;

        for (int i = int(numbers.size()) + 1; i < ((part == 1) ? 30000001 : 2021); i++)
        {
            speak = next;

            if (lastSpoken[speak] != 0)
            {
                next = i - lastSpoken[speak];
            }
            else
            {
                next = 0;
            }
            lastSpoken[speak] = i;
        }

        LOG(DBG, "P1: " << speak);
        return speak;
    }

    virtual void RunOnce() override
    {
        {
            PROFILE_SCOPE(Part1);
            part1 = std::to_string(Parts(0));
        }
        
        {
            PROFILE_SCOPE(Part2);
            part2 = std::to_string(Parts(1));
        }
    }

    virtual void DrawGUI() override
    {
        PROFILE_SCOPE(GUI);
        if (ImGui::Begin("Results"))
        {

            ImGui::Text(fmt::format("Part1: {}", part1).c_str());
            ImGui::Text(fmt::format("Part2: {}", part2).c_str());
        }
        ImGui::End();
    }
};


REGISTER_PROBLEM(AOC_2020_Day15)
