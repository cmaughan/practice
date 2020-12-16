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
REGISTER_PROBLEM(AOC_2020_Day8)
{
    PROFILE_SCOPE(Solution);

    std::vector<std::string> lines;
    auto in = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_8.txt"));

    enum class OpCode { nop, acc, jmp };
    struct Instruction
    {
        OpCode op;
        int A;
    };

    std::vector<Instruction> program;
    for (auto& line : in)
    {
        Instruction inst;
        auto tok = string_split(line, " ");

        if (tok[0] == "nop")
        {
            inst.op = OpCode::nop;
        }
        else if (tok[0] == "acc")
        {
            inst.op = OpCode::acc;
        }
        else if (tok[0] == "jmp")
        {
            inst.op = OpCode::jmp;
        }
        inst.A = std::stoi(tok[1]);
        program.push_back(inst);
    }

    int regA = 0;
    auto execute = [&]()
    {
        std::set<int> visited;
        int pc = 0;
        regA = 0;
        for (;;)
        {
            if (visited.find(pc) != visited.end())
            {
                return false;
            }
            visited.insert(pc);

            if (pc == program.size())
                return true;

            auto& inst = program[pc];
            switch (inst.op)
            {
            case OpCode::nop:
                pc++;
                break;
            case OpCode::jmp:
                pc += inst.A;
                break;
            case OpCode::acc:
                regA += inst.A;
                pc++;
                break;
            }

        }
    };

    execute();
    part1 = std::to_string(regA);

    for (auto& inst : program)
    {
        auto kept = inst.op;
        if (inst.op == OpCode::nop)
        {
            inst.op = OpCode::jmp;
        }
        else if (inst.op == OpCode::jmp)
        {
            inst.op = OpCode::nop;
        }

        if (execute())
        {
            part2 = std::to_string(regA);
            break;
        }

        inst.op = kept;

    }

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


