#include "common.h"

#include <cassert>
#include <limits>
#include <fstream>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2017_Day8)
{
    Timer t("Day8 Timer");
    std::ifstream p8in(PRACTICE_ROOT "/advent_of_code/2017/inputs/p8input.txt");
    assert(p8in.is_open());
    std::stringstream p8buffer;
    p8buffer << p8in.rdbuf();
    auto p8grid = string_get_string_grid(p8buffer.str());
    enum inputEntry { Reg1, Op, Val1, If, Reg2, Cmp, Val2 };
    struct regVal { int v = 0; void inc(int val) { v += val; } };
    enum class OpType { LESS, GREATER, LEQUAL, GEQUAL, NOTEQUAL, EQUAL };
    std::map<string, regVal> registers;
    std::map<string, OpType> toOp{ { "<", OpType::LESS }, { ">", OpType::GREATER }, {"<=", OpType::LEQUAL}, {">=", OpType::GEQUAL}, {"!=", OpType::NOTEQUAL}, { "==", OpType::EQUAL} };
    int maxVal = std::numeric_limits<int>::min();
    for (auto& line : p8grid)
    {
        bool should = false;
        int val2 = stoi(line[Val2]);
        switch (toOp[line[Cmp]])
        {
        case OpType::LESS:
            should = registers[line[Reg2]].v < val2;
            break;
        case OpType::GREATER:
            should = registers[line[Reg2]].v > val2;
            break;
        case OpType::LEQUAL:
            should = registers[line[Reg2]].v <= val2;
            break;
        case OpType::GEQUAL:
            should = registers[line[Reg2]].v >= val2;
            break;
        case OpType::NOTEQUAL:
            should = registers[line[Reg2]].v != val2;
            break;
        case OpType::EQUAL:
            should = registers[line[Reg2]].v == val2;
            break;
        }
        if (should)
        {
            int val1 = stoi(line[Val1]);
            if (line[Op] == "dec")
                val1 = -val1;
            registers[line[Reg1]].inc(val1);
            maxVal = std::max(maxVal, registers[line[Reg1]].v);
        }
    }
    LOG(INFO) << "P8,1: " << std::max_element(registers.begin(), registers.end(), [](const std::pair<std::string, regVal>& r1, const std::pair<std::string, regVal>& r2)
    {
        return r1.second.v < r2.second.v;
    })->second.v;

    LOG(INFO) << "P8,2: " << maxVal;
}
