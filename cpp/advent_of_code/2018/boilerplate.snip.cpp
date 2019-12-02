#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"

#include <glm/glm.hpp>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(Problem1)
{
    /*std::istringstream iss(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_5.txt"));
    std::vector<string> lines;
    for (std::string line; std::getline(iss, line); )
    {
        lines.push_back(line);
    }
    std::sort(lines.begin(), lines.end());
    for (auto& l : lines)
    {
        int year, hour, month, day, minute;
        sscanf(l.c_str(), "[%d-%d-%d %d:%d] %s %s", &year, &month, &day, &hour, &minute, word1, word2);
    }
    */
    
    //auto input = string_split(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_2.txt"));


    LOG(INFO) << "Part 1: " << 1;
    LOG(INFO) << "Part 2: " << 2;
}

