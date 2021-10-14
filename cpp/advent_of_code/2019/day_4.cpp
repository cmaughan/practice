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

REGISTER_PROBLEM(AOC_2019_Day4)
{
    uint64_t low = 246515;
    uint64_t high = 739105;

    uint32_t count = 0;
    for (auto current = low; current <= high; current++)
    {
        auto str = std::to_string(current);
        int last = 0;
        int i = 0;
        int doubles = 0;
        bool foundPair = false;
        for (i = 0; i < str.length(); i++)
        {
            if (str[i] < last)
                break;
            if (last == str[i])
            {
                doubles++;
            }
            else if (doubles == 1)
            {
                foundPair = true;
                doubles = 0;
            }
            last = str[i];
        }

        if (doubles == 1)
            foundPair = true;

        if (i < str.length() || !foundPair)
            continue;

        count++;
    }
    LOG(INFO) << "Day2: " << count;
}

