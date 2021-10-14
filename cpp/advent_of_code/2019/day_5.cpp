#include "common.h"
#include "mutils/file/file.h"
#include "mutils/string/stringutils.h"
#include "mutils/algorithm/containerutils.h"

#include <magic_enum/magic_enum.hpp>

#include <algorithm>
#include <numeric>
#include <functional>
#include <set>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include "glm/gtx/hash.hpp"

using namespace std;
using namespace MUtils;
using namespace magic_enum;

REGISTER_PROBLEM(AOC_2019_Day5)
{
    auto in = string_get_integers(file_read(PRACTICE_ROOT "/advent_of_code/2019/inputs/day_5.txt"));

    enum class Mode
    {
        position = 0,
        immediate = 1
    };

    struct Param
    {
        Mode mode;
        int value;
    };

    enum class OpCode
    {
        add = 1,
        multiply = 2,
        input = 3,
        output = 4,
        jump_if_true = 5,
        jump_if_false = 6,
        less = 7,
        equal = 8,
        exit = 99,
        invalid
    };

    std::map<OpCode, int> opCodeValues =
    {
        { OpCode::add, 3 },
        { OpCode::multiply, 3 },
        { OpCode::input, 1 },
        { OpCode::output, 1 },
        { OpCode::exit, 0},
        { OpCode::jump_if_true, 2},
        { OpCode::jump_if_false, 2},
        { OpCode::less, 3},
        { OpCode::equal, 3},
        { OpCode::invalid, 0}
    };

    struct Instruction
    {
        OpCode opCode;
        std::vector<Param> parameters;
    };

    auto parseInstruction = [&](int& index)
    {
        Instruction inst;
        auto strInst = std::to_string(in[index]);
        while (strInst.length() < 5)
            strInst = "0" + strInst;
        inst.opCode = OpCode(std::stoi(strInst.substr(strInst.length() - 2)));
        int pos = int(strInst.length()) - 3;

        auto itr = opCodeValues.find(inst.opCode);
        assert(itr != opCodeValues.end());

        index++;

        int parameterCount = itr->second;
        while (parameterCount-- > 0)
        {
            Param param;
            param.mode = enum_cast<Mode>(strInst[pos--] - '0').value_or(Mode::immediate);
            param.value = in[index++];
            inst.parameters.push_back(param);
        }
        return inst;
    };

    int inputIndex = 0;
    std::vector<int> input = { 5 };
    int pc = 0;

    auto read = [&](const Param& p) { return p.mode == Mode::position ? in[p.value] : p.value;  };
    auto write = [&](const Param& p, int arg) { p.mode == Mode::position ? in[p.value] = arg : assert("Invalid immediate write?");  };

    std::map<OpCode, std::function<void(Instruction & index)>> operations;
    operations[OpCode::input] = [&](Instruction& inst) { write(inst.parameters[0], input[inputIndex++]); };
    operations[OpCode::output] = [&](Instruction& inst) { LOG(INFO) << "Out: " << read(inst.parameters[0]); };
    operations[OpCode::add] = [&](Instruction& inst) { write(inst.parameters[2], read(inst.parameters[0]) + read(inst.parameters[1])); };
    operations[OpCode::multiply] = [&](Instruction& inst) { write(inst.parameters[2], read(inst.parameters[0]) * read(inst.parameters[1])); };
    operations[OpCode::jump_if_true] = [&](Instruction& inst) { if (read(inst.parameters[0]) != 0) { pc = read(inst.parameters[1]); } };
    operations[OpCode::jump_if_false] = [&](Instruction& inst) { if (read(inst.parameters[0]) == 0) { pc = read(inst.parameters[1]); } };
    operations[OpCode::less] = [&](Instruction& inst) {
        int val = 0;
        if (read(inst.parameters[0]) < read(inst.parameters[1]))
        {
            val = 1;
        }
        write(inst.parameters[2], val);
    };

    operations[OpCode::equal] = [&](Instruction& inst)
    {
        int val = 0;
        if (read(inst.parameters[0]) == read(inst.parameters[1]))
        {
            val = 1;
        }
        write(inst.parameters[2], val);
    };
    operations[OpCode::exit] = [&](Instruction& inst) { pc = int(in.size()); };
    operations[OpCode::invalid] = [&](Instruction& inst) { assert(!"Invalid opcode"); pc = int(in.size()); };

    // Interpret the program
    while (pc < in.size())
    {
        auto inst = parseInstruction(pc);
        
        auto itr = operations.find(inst.opCode);
        if (itr != operations.end())
        {
            itr->second(inst);
        }
        else
        {
            assert(!"invalid opcode?");
        }
    }
}

