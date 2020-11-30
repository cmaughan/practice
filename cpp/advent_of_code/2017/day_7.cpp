#include "common.h"

using namespace MUtils;

REGISTER_PROBLEM(AOC_2017_Day7)
{
    // P7:1
    auto p7input = file_read(PRACTICE_ROOT "/advent_of_code/2017/inputs/p7input.txt");
   
    std::vector<std::string> lines;
    string_split_lines(p7input, lines);

    // A tower disc
    struct disc
    {
        std::string name;
        int weight = 0;
        int childWeights = 0;
        disc* pParent = nullptr;
        std::vector<std::string> childNames;
        std::vector<disc*> children;

        int UpdateWeights()
        {
            childWeights += weight;
            for (auto& ch : children)
            {
                childWeights += ch->UpdateWeights();
            }
            return childWeights;
        }

        disc* FindUnbalanced()
        {
            disc* pRet;
            for (auto& child : children)
            {
                if (!child->Balanced(&pRet))
                {
                    return pRet->FindUnbalanced();
                }
            }
            return this;
        }

        bool Balanced(disc** ppDisc)
        {
            struct mapVal { int v = 0; disc* pDisc = nullptr; void inc(disc* p) { v++; pDisc = p; } };
            std::map<int, mapVal > mapCounts;
            std::for_each(children.begin(), children.end(), [&mapCounts](disc* p) {mapCounts[p->childWeights].inc(p); });
            auto itr = std::find_if(mapCounts.begin(), mapCounts.end(), [&mapCounts](const std::pair<int, mapVal>& entry) { return entry.second.v == 1; });
            if (itr == mapCounts.end())
                return true;
            *ppDisc = itr->second.pDisc;
            return false;
        }
    };
    std::map<std::string, std::shared_ptr<disc>> discs;

    // Pass 1, read the discs
    for (auto& line : lines)
    {
        auto towerEntry = string_split(line, " \t,");
        if (towerEntry.empty())
            continue;
        auto d = std::make_shared<disc>();
        d->name = towerEntry[0];
        d->weight = stoi(string_trim(towerEntry[1], "()"));

        for (int index = 3; index < towerEntry.size(); index++)
        {
            d->childNames.push_back(towerEntry[index]);
        }
        discs[d->name] = d;
    }

    // Pass 2, build the hierarhcy
    for (auto& d : discs)
    {
        auto& pDisc = d.second;
        for (auto& childName : pDisc->childNames)
        {
            auto itrFound = discs.find(childName);
            if (itrFound != discs.end())
            {
                pDisc->children.push_back(itrFound->second.get());
                itrFound->second->pParent = pDisc.get();
            }
        }
    }

    // Get the root
    auto pRoot = std::find_if(discs.begin(), discs.end(), [](const std::pair<std::string, std::shared_ptr<disc>>& p) { return p.second->pParent == nullptr; })->second;
    LOG(INFO, "P7,1: " << pRoot->name);

    // Build the weights, find the unbalanced disc
    pRoot->UpdateWeights();
    auto pRet = pRoot->FindUnbalanced();
    auto itrSibling = std::find_if(pRet->pParent->children.begin(), pRet->pParent->children.end(), [pRet](disc* pChild) { return pChild != pRet; });

    // Balance result is the discs weight difference from the sibling
    LOG(INFO, "P7,2: " << pRet->weight - (pRet->childWeights - (*itrSibling)->childWeights));
}
