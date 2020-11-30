#include "common.h"

#include <cassert>
#include <limits>
#include <algorithm>
#include <cstdint>
#include <numeric>
#include <glm/glm.hpp>
#include <set>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2017_Day12)
{
    //8 <-> 432, 3
    std::map<int, std::set<int>> program_pipes;
    auto lines = string_get_string_grid(file_read(PRACTICE_ROOT "/advent_of_code/2017/inputs/p12input.txt"));
    for (auto l : lines)
    {
        auto id = std::stoi(l[0]);
        for (int i = 2; i < l.size(); i++)
        {
            program_pipes[id].insert(std::stoi(l[i]));
        }
    }


    bool inserted = false;
    do
    {
        inserted = false;
        for (auto p : program_pipes) // 0 -> 1,2,3
        {
            for (auto pipe : p.second) //  1, 2, 3
            {
                for (auto child_pipe : program_pipes[pipe]) // 1->abc, 2->abc, 3->abc
                {
                    auto itr = program_pipes[p.first].insert(child_pipe);
                    if (itr.second)
                    {
                        inserted = true;
                    }
                }
            }
        }
    } while (inserted);

    LOG(INFO, "Part1 : " << program_pipes[0].size());

    std::vector<std::set<int>> groups;
    for (auto p : program_pipes)
    {
        bool found = false;
        for (auto g : groups)
        {
            std::vector<int> intersects;
            std::set_intersection(g.begin(), g.end(), p.second.begin(), p.second.end(), std::back_inserter(intersects));
            if (!intersects.empty())
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            groups.push_back(p.second);
        }
    }
    LOG(INFO, "Part2 : " << groups.size());

}
