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

REGISTER_PROBLEM(AOC_2019_Day6)
{
    auto in = string_split(file_read(PRACTICE_ROOT "/advent_of_code/2019/inputs/day_6.txt"), "\n)\r");

    struct Node
    {
        Node(const std::string& n) : name(n) {}
        std::string name;
        std::vector<Node*> children;
        Node* pParent = nullptr;
    };
    std::map<std::string, std::shared_ptr<Node>> mapNameToNode;

    for (uint32_t i = 0; i < (uint32_t)in.size(); i += 2)
    {
        auto reg = [&](auto name) {
            auto itrFound = mapNameToNode.find(name);
            if (itrFound == mapNameToNode.end())
            {
                auto pNode = std::make_shared<Node>(name);
                mapNameToNode[name] = pNode;
                return pNode;
            }
            return itrFound->second;
        };

        auto pParent = reg(in[i]);
        auto pChild = reg(in[i + 1]);
        pParent->children.push_back(pChild.get());
        pChild->pParent = pParent.get();
    }

    int count = 0;
    for (auto& pNode : mapNameToNode)
    {
        auto pCurrent = pNode.second.get();
        while (pCurrent->pParent)
        {
            count++;
            pCurrent = pCurrent->pParent;
        }
    }
    LOG(INFO) << "Day1: " << count;

    auto pYou = mapNameToNode["YOU"];
    auto pSan = mapNameToNode["SAN"];

    int minCount = std::numeric_limits<int>::max();

    // Find the common parent
    int outerCount = 0;
    auto pSource = pYou->pParent;
    while (pSource)
    {
        int innerCount = 0;
        auto pDest = pSan->pParent;
        while (pDest)
        {
            if (pDest == pSource)
            {
                minCount = std::min(minCount, outerCount + innerCount);
            }
            pDest = pDest->pParent;
            innerCount++;
        }

        pSource = pSource->pParent;
        outerCount++;
    }

    LOG(INFO) << "Day2: " << minCount;
}

