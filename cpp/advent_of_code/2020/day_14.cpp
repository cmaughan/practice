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

#define BEGIN_ONCE static Once once([]()
#define END_ONCE ); 

    //mask = 0X10110X1001000X10X00X01000X01X01101
    //mem[49559] = 97
    //mem[18692] = 494387917k

    struct Write
    {
        std::uint64_t andMask;
        std::uint64_t orMask;
        std::uint64_t xCount;
        std::vector<std::pair<uint64_t, uint64_t>> writes;
    };

    std::vector<Write> Read()
    {
        /*
        auto str = R"(mask = 000000000000000000000000000000X1001X
mem[42] = 100
mask = 00000000000000000000000000000000X0XX
mem[26] = 1)";
*/

        std::vector<Write> writes;
        PROFILE_SCOPE(Read);
        //auto in = string_split(str/*file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_14.txt")*/, "\r\n=[] ");
        auto in = string_split(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_14.txt"), "\r\n=[] ");

        Write write;
        for (uint64_t index = 0; index < in.size(); index++)
        {
            auto str = in[index];
            if (str == "mask")
            {
                if (index != 0)
                {
                    writes.push_back(write);
                    write.writes.clear();
                }

                index++;
                str = in[index];

                uint64_t andMask = 0;
                uint64_t orMask = 0;
                uint64_t xCount = 0;
                uint64_t shift = str.size() - 1;
                for (auto& ch : str)
                {
                    if (ch == '1')
                    {
                        orMask |= (1ull << shift);
                    }
                    else if (ch == 'X')
                    {
                        andMask |= (1ull << shift);
                        xCount++;
                    }
                    else if (ch == '0')
                    {
                    }
                    else
                    {
                        assert(!"!Invalid");
                    }
                    shift--;
                }
                write.andMask = andMask;
                write.orMask = orMask;
                write.xCount = xCount;
            }
            else if (str == "mem")
            {
                write.writes.push_back(std::make_pair(stoull(in[index + 1]), stoull(in[index + 2])));
                index += 2;
            }
        }
        writes.push_back(write);
        return writes;
    }

    uint64_t Part1()
    {
        auto writes = Read();

        PROFILE_SCOPE(Part1);
        uint64_t total = 0;

        std::map<uint64_t, uint64_t> memory;
        for (auto& write : writes)
        {
            for (const auto& [mem, val] : write.writes)
            {
                // (keep existing) | 
                memory[mem] = (val & write.andMask) | write.orMask;
            }
        }

        for (const auto& [mem, val] : memory)
        {
            total += val;
        }

        LOG(DBG, "P1: " << total);
        return total;
    }


    uint64_t Part2()
    {
        auto writes = Read();

        PROFILE_SCOPE(Part2);
        uint64_t total = 0;

        std::map<uint64_t, uint64_t> memory;
        for (auto& write : writes)
        {
            for (auto [mem, val] : write.writes)
            {
                mem |= write.orMask;

                // Remove x's
                mem &= ~write.andMask;

                for (int i =0; i < (1 << write.xCount); i++)
                {
                    auto address = mem | _pdep_u64(i, write.andMask);
                    memory[address] = val;
                }
            }
        }

        for (const auto& [mem, val] : memory)
        {
            total += val;
        }

        LOG(DBG, "P1: " << total);
        return total;
    }

};

/*
REGISTER_PROBLEM(AOC_2020_Day14)
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


