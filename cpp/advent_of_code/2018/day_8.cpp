#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"
#include <glm/glm.hpp>

using namespace std;

REGISTER_PROBLEM(AOC_2018_Day8)
{
    //auto s = file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_8.txt");

    std::vector<uint8_t> contents;
    std::ifstream in(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_8.txt", std::ios::in | std::ios::binary);
    if (in)
    {
        in.seekg(0, std::ios::end);
        contents.resize(size_t(in.tellg()));
        in.seekg(0, std::ios::beg);
        in.read((char*)&contents[0], contents.size());
        in.close();
    }

    std::vector<int> input;
    for (auto entry : contents)
    {
        if (entry == 0)
            continue;
        if (entry == 0xFF)
            continue;
        if (entry == 32)
            continue;
        if (entry == 0xFE)
            continue;
        //if (entry == 0 || entry == 32 || entry = 0xFF || entry == 0xFE)
        //    continue;
        input.push_back(entry - '0');
    }
    /*return std::string();
    std::vector<int> input;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 0 || s[i] == 0xFF || s[i] == 0xFE || s[i] == 0x20)
            continue;
        input.push_back(s[i]);j
    }*/
    //auto in_text = file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_8.txt");
    //auto input = utils_get_integers(in_text);

    struct node
    {
        std::vector<int> meta_data;
        node* parent = nullptr;
        std::vector<node*> children;
    };
    node* pRoot = new node();
    node* pCurrent = pRoot;

    int meta_count = 0;
    std::function<void(std::vector<int>::iterator, node* pParent)> fnParse;
    fnParse = [&](std::vector<int>::iterator itr, node* pParent)
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
    LOG(INFO) << "Part 2: " << 2;
}

