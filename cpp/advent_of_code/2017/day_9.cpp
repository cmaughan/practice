#include "common.h"
#include "utils.h"
#include "fileutils.h"

#include <cassert>
#include <limits>
#include <fstream>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2017_Day9)
{
    auto text = file_read(PRACTICE_ROOT "/advent_of_code/2017/inputs/p9input.txt");
    assert(!text.empty());

    bool skip = false;
    bool in_garbage = false;
    int group_count = 0;
    int group_depth = 0;
    int garbage_count = 0;
    for (auto& ch : text)
    {
        if (skip)
        {
            skip = false;
            continue;
        }

        if (ch == '!')
        {
            skip = true;
            continue;
        }

        if (!in_garbage && ch == '<')
        {
            in_garbage = true;
            continue;
        }
        else if (ch == '>')
        {
            in_garbage = false;
            continue;
        }

        if (in_garbage)
        {
            garbage_count++;
        }
        else
        {
            if (ch == '{')
            {
                group_depth++;
            }
            else if (ch == '}')
            {
                group_count+=group_depth;
                group_depth--;
            }
        }
    }

    LOG(INFO) << "Part 1: " << group_count;
    LOG(INFO) << "Part 2: " << garbage_count;
}
