#include "common.h"

#include <algorithm>
#include <fstream>
#include <numeric>
#include <regex>
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
REGISTER_PROBLEM(AOC_2020_Day4)
{
    PROFILE_SCOPE(Solution);

    std::vector<std::string> lines;
    auto in = file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_4.txt");

    std::set<std::string> checkKeys({ "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" });
    std::map<std::string, std::regex> keyRegex({
        { "byr" , std::regex("^(19[2-9][0-9]|200[0-2])$") },
        { "iyr" , std::regex("^(201[0-9]|2020)$") },
        { "eyr" , std::regex("^(202[0-9]|2030)$") },
        { "hgt" , std::regex("^(59|6[0-9]|7[0-6]in)|(1[5-8][0-9]|19[0-3])cm)$") },
        { "hcl" , std::regex("^(#[0-9a-f]{6})$") },
        { "ecl" , std::regex("^(amb|blu|brn|gry|grn|hzl|oth)$") },
        { "pid" , std::regex("^([0-9]{9})$") },
        });
    std::set<std::string> checkColors({ "amb", "blu", "brn", "gry", "grn", "hzl", "oth" });

    using Passport = std::map<std::string, std::string>;
    auto validate = [&](Passport& p) -> bool {
        bool valid = true;
        std::for_each(checkKeys.begin(), checkKeys.end(), [&](auto& key) {

            if (p.find(key) == p.end() || !std::regex_match(p[key], keyRegex[key]))
            {
                valid = false;
            }
        });
        return valid;
    };

    int valid = 0;
    Passport currentPass;

    auto groups = string_split_delim_string(in, "\r\n\r\n");
    for (auto& g : groups)
    {
        for (auto& line : string_split_lines(g))
        {
            auto tokens = string_split(line, ": ");
            auto itr = tokens.begin();
            while (itr < tokens.end())
            {
                auto key = *itr++;
                auto value = *itr++;
                currentPass[key] = value;
            }
        }
        if (validate(currentPass))
            valid++;
        
        currentPass.clear();
    }

    part2 = std::to_string(valid);

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


