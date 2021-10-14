#include "common.h"
#include "mutils/file/file.h"
#include "mutils/string/stringutils.h"
#include "mutils/algorithm/containerutils.h"

#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2019_Day2)
{
    auto in = string_get_integers(file_read(PRACTICE_ROOT "/advent_of_code/2019/inputs/day_2.txt"));

    // Declare math ops as functors
    std::map<int, std::function<void(std::vector<int>&, int&)>> ops;
    ops[1] = [&](auto& mem, int& pc) { mem[mem[pc + 3]] = mem[mem[pc + 1]] + mem[mem[pc + 2]]; pc += 4; };
    ops[2] = [&](auto& mem, int& pc) { mem[mem[pc + 3]] = mem[mem[pc + 1]] * mem[mem[pc + 2]]; pc += 4; };

    auto testNounVerb = [&](int noun, int verb) {
        std::vector<int> mem = in;

        mem[1] = noun;
        mem[2] = verb;

        int pc = 0;
        while (pc < mem.size())
        {
            if (mem[pc] == 99)
                break;

            auto itrCode = ops.find(mem[pc]);
            if (itrCode != ops.end())
            {
                itrCode->second(mem, pc);
            }
        }
        return mem[0];
    };

    LOG(INFO) << "Day1: " << testNounVerb(12, 2);

    // Search
    for (int noun = 0; noun <= 99; noun++)
    {
        for (int verb = 0; verb <= 99; verb++)
        {
            if (testNounVerb(noun, verb) == 19690720)
            { 
                LOG(INFO) << "Day2: " << (100 * noun + verb);
                break;
            }
        }
    }
}

