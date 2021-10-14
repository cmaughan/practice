#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2018_Day11)
{
    const int64_t total_size = 301;

    std::vector<int64_t> vals;
    vals.resize(total_size * total_size);

    auto get_val = [&](int x, int y)
        -> int64_t&
    {
        return vals[(y * total_size) + x];
    };

    const int64_t input = 3628;
    for (int y = 0; y < total_size; y++)
    {
        for (int x = 0; x < total_size; x++)
        {
            int64_t rackID = x + 10;
            int64_t power = rackID * y;
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
            get_val(x, y) = power;
        }
    }

    int64_t best = 0;
    glm::ivec3 bestCoord;

    auto calc_sub_grid = [&](int sub_grid_size)
    {

        for (int y = 0; y < total_size - sub_grid_size; y++)
        {
            for (int x = 0; x < total_size - sub_grid_size; x++)
            {
                int64_t total = 0;
                for (int yy = 0; yy < sub_grid_size; yy++)
                {
                    for (int xx = 0; xx < sub_grid_size; xx++)
                    {
                        total += get_val(x + xx, y + yy);
                    }
                }
                if (total > best)
                {
                    bestCoord = glm::ivec3(x, y, sub_grid_size);
                    best = total;
                }
            }
        }
    };

    // Part 1
    Timer part1("Timing:", true);

    calc_sub_grid(3);

    LOG(INFO) << "Part1: " << glm::to_string(bestCoord);
    part1.Stop();

    // Part 2
    Timer part2("Timing:");
    best = 0;
    for (int sub_grid_size = 3; sub_grid_size < total_size; sub_grid_size++)
    {
        calc_sub_grid(sub_grid_size);
    }

    LOG(INFO) << glm::to_string(bestCoord);
}

