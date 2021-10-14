#include "common.h"

#include "glm/glm.hpp"
#include <glm/gtx/hash.hpp>

using namespace std;
using namespace MUtils;

glm::ivec2 UlamIndexToCoords(int n)
{
    const auto k = std::ceil((std::sqrt(n) - 1) / 2);
    auto t = 2 * k + 1;
    auto m = std::pow(t, 2);

    t -= 1;

    if (n >= m - t)
    {
        return glm::ivec2(k - (m - n), -k);
    }

    m -= t;

    if (n >= m - t) {
        return glm::ivec2(-k, -k + (m - n));
    }

    m -= t;

    if (n >= m - t)
    {
        return glm::ivec2(-k + (m - n), k);
    }

    return glm::ivec2(k, k - (m - n - t));
};

REGISTER_PROBLEM(AOC_2017_Day3)
{
    // P3, 1: Spiral Memory
    auto coord = UlamIndexToCoords(368078);
    LOG(INFO, "P3,1" << std::abs(coord.x) + std::abs(coord.y));

    // P3, 2: Walk and accumulate surrounds 
    std::unordered_map<glm::ivec2, int> spiralVals{ { glm::ivec2(0, 0), 1 } };
    std::vector<glm::ivec2> surrounds{ {1, 0}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {-1, 1}, {0, 1}, {1, 1} };
    int currentIndex = 1;
    do
    {
        coord = UlamIndexToCoords(++currentIndex);
        for (auto& offset : surrounds)
        {
            auto itr = spiralVals.find(coord + offset);
            spiralVals[coord] += (itr != spiralVals.end() ? itr->second : 0);
        }
    } while (spiralVals[coord] < 368078);
    LOG(INFO, "P3,2" << spiralVals[coord]);
}
