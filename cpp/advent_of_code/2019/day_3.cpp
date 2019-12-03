#include "common.h"
#include "mutils/file/file.h"
#include "mutils/string/stringutils.h"
#include "mutils/algorithm/containerutils.h"

#include <algorithm>
#include <numeric>
#include <functional>
#include <set>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include "glm/gtx/hash.hpp"

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2019_Day3)
{
    std::unordered_map<glm::ivec2, int> locations;

    auto in = string_get_string_grid(file_read(PRACTICE_ROOT "/advent_of_code/2019/inputs/day_3.txt"));

    int minDistance = std::numeric_limits<int>::max();
    int minSteps = std::numeric_limits<int>::max();

    glm::ivec2 currentLocation(0, 0);

    int steps = 0;
    auto move = [&](int x, int y, int wire) {
        // Each step along the wire is a delta in x & y
        glm::ivec2 delta(0);
        if (x != 0)
        {
            delta.x = x > 0 ? 1 : -1;
        }
        else if (y != 0)
        {
            delta.y = y > 0 ? 1 : -1;
        }

        // Walk the wire
        for (int count = 0; count < std::max(std::abs(x), std::abs(y)); count++)
        {
            steps++;
            currentLocation += delta;
            if (wire == 0)
            {
                // First wire, store the min steps if not stored yet
                if (locations.find(currentLocation) == locations.end())
                {
                    locations[currentLocation] = steps;
                }
            }
            // Second wire, check for a collision and calculate min steps for each wire or min distance
            else if (locations.find(currentLocation) != locations.end())
            {
                minDistance = std::min(glm::abs(currentLocation).x + glm::abs(currentLocation).y, minDistance);
                minSteps = std::min(minSteps, locations[currentLocation] + steps);
            }
        }
    };

    for (int wire = 0; wire < 2; wire++)
    {
        // Each wire, reset the location and the step count
        currentLocation = glm::ivec2(0, 0);
        steps = 0;
        for (auto& command : in[wire])
        {
            if (command[0] == 'L')
            {
                move(-stoi(command.substr(1)), 0, wire);
            }
            else if (command[0] == 'R')
            {
                move(stoi(command.substr(1)), 0, wire);
            }
            else if (command[0] == 'U')
            {
                move(0, -stoi(command.substr(1)), wire);
            }
            else if (command[0] == 'D')
            {
                move(0, stoi(command.substr(1)), wire);
            }
        }
    }
    LOG(INFO) << "Part1 :" << minDistance;
    LOG(INFO) << "Part2 :" << minSteps;
}

