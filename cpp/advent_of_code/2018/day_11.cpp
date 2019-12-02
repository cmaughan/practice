#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"
#include <glm/glm.hpp>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2018_Day11)
{
    uint64_t input = 3628;
    uint64_t max_power = 0;
    glm::ivec2 best;
    int width = 300;
    std::vector<uint64_t> vals;
    auto val = [&](int x, int y)
        -> uint64_t &
    {
        return vals[y * width + x];
    };

    for (int y = 1; y < 301; y++)
    {
        for (int x = 1; x < 301; x++)
        {
            uint64_t rackID = x + 10;
            uint64_t power = rackID * y;
            power += input;
            power = power * rackID;
            auto str = std::to_string(power);
            if (str.length() < 3)
            {
                power = 0;
            }
            else
            {
                power = str[str.size() - 3] - '0';
            }
            power -= 5;
            if (power > max_power)
            {
                max_power = power;
                best = glm::ivec2(x, y);
            }
        }
    }

    LOG(INFO) << "Part 1: " << best.x << ", " << best.y;
    LOG(INFO) << "Part 2: " << 2;
}

