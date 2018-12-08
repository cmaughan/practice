#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"
#include <glm/glm.hpp>
#include <algorithm>
#include <numeric>

using namespace std;

REGISTER_PROBLEM(AOC_2018_Day8)
{
    std::ostringstream str;
    auto contents = file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_8.txt");
    //contents = "2 3 0 3 10 11 12 1 1 0 1 99 2 1 1 2";
    // Hack the input - binary?!
    uint8_t* p = (uint8_t*)&contents[0];
    while (p != (uint8_t*)&contents[contents.size()])
    {
        if (*p != 0 && *p != 0xFF && *p != 0xFE)
        {
            str << p;
        }
        p++;
    }
    auto input = utils_get_integers(str.str());

    struct node
    {
        std::vector<int> meta_data;
        node* parent = nullptr;
        std::vector<node*> children;
    };
    node* pRoot = new node();
    node* pCurrent = pRoot;

    int meta_count = 0;
    std::function<void(std::vector<int>::iterator&, node* pParent)> fnParse;
    fnParse = [&](std::vector<int>::iterator& itr, node* pParent)
    {
        node* pNewNode = new node();
        pNewNode->parent = pParent;
        pParent->children.push_back(pNewNode);
        int children = *itr++;
        pNewNode->meta_data.resize(*itr++);
        for (int i = 0; i < children; i++)
        {
            fnParse(itr, pNewNode);
        }
        for (int i = 0; i < pNewNode->meta_data.size(); i++)
        {
            int c = *itr++;
            meta_count += c;
            pNewNode->meta_data[i] = c;
        }
    };

    fnParse(input.begin(), pRoot);
    LOG(INFO) << "Part 1: " << meta_count;
   
    meta_count = 0;
    std::function<void(node*)> fnVisit;
    fnVisit = [&](node* pNode)
    {
        if (pNode->children.empty())
        {
            meta_count += std::accumulate(pNode->meta_data.begin(), pNode->meta_data.end(), 0, [](int total, int val) { return total + val; });
        }
        for (auto& child_index : pNode->meta_data)
        {
            if (pNode->children.size() > (child_index -1))
            {
                fnVisit(pNode->children[child_index - 1]);
            }
        }
    };
    for (auto pVisit : pRoot->children)
    {
        fnVisit(pVisit);
    }

    LOG(INFO) << "Part 2: " << meta_count;
}

