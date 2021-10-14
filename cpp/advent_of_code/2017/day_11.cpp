#include "common.h"

#include <cassert>
#include <limits>
#include <algorithm>
#include <cstdint>
#include <numeric>
#include <glm/glm.hpp>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2017_Day11)
{
    auto input = string_split(file_read(PRACTICE_ROOT "/advent_of_code/2017/inputs/p11input.txt"), ",");
    
    // http://3dmdesign.com/development/hexmap-coordinates-the-easy-way
    // Coordinate system; n/s is +/-y
    // nw/se are on the same y plane
    std::map<std::string, glm::ivec2> dir_to_offset{
        { "n", glm::ivec2(0, 1) },
        { "s", glm::ivec2(0, -1) },
        { "ne", glm::ivec2(1, 1) },
        { "nw", glm::ivec2(-1, 0) },
        { "se", glm::ivec2(1, 0) },
        { "sw", glm::ivec2(-1, -1) } };
   
    // Walk to each one, tracking max distance
    glm::ivec2 coord(0, 0);
    int max_dist = 0;
    std::for_each(input.begin(), input.end(), [&](const std::string& str)
    {
        coord += dir_to_offset[str];
        
        max_dist = std::max(max_dist, std::abs(coord.x));
        max_dist = std::max(max_dist, std::abs(coord.y));
        max_dist = std::max(max_dist, std::abs(coord.x - coord.y));
    });

    // distance
    int dist = std::max(0, std::abs(coord.x));
    dist = std::max(dist, std::abs(coord.y));
    dist = std::max(dist, std::abs(coord.x - coord.y));
    LOG(INFO, "Part 1: " << dist);
    LOG(INFO, "Part 2: " << max_dist);
}
