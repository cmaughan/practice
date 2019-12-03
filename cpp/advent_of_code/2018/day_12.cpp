#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <deque>
using namespace std;
using namespace MUtils;

const std::string testInput = R"(initial state: #..#.#..##......###...###

...## => #
..#.. => #
.#... => #
.#.#. => #
.#.## => #
.##.. => #
.#### => #
#.#.# => #
#.### => #
##.#. => #
##.## => #
###.. => #
###.# => #
####. => #)";

REGISTER_PROBLEM(AOC_2018_Day12)
{

    //initial state: #........#.#.#...###..###..###.#..#....###.###.#.#...####..##..##.#####..##...#.#.....#...###.#.####
    //#..## => .
    std::map<std::string, char> rules;
    auto lines = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_10.txt"));

    lines = string_split_lines(testInput);

    auto source = lines[0].substr(lines[0].find_first_of("#."));
    for (int line = 1; line < lines.size(); line++)
    {
        if (lines[line].empty())
            continue;

        auto rule = lines[line];
        auto split_rule = string_split(rule, " ");
        rules[split_rule[0]] = split_rule[2][0];
    }

    int startPot = 0;
    for (int generation = 0; generation < 20; generation++)
    {
        // 2 empty slots in front
        std::string target;
        int index = -1;
        while (index <= source.size())
        {
            for (auto& rulePair : rules)
            {
                int iCh;
                int testIndex = 0;
                for (iCh = index - 2; iCh < (index + 2); iCh++)
                {
                    char t = (iCh < 0 || iCh >= source.length()) ? '.' : source[index];
                    if (rulePair.first[testIndex++] != t)
                    {
                        break;
                    }
                }

                if (iCh == (index + 2))
                { 
                    target.push_back(rulePair.second);
                }
                else if (index >= 0)
                {
                    target.push_back('.');
                }
            }

            index++;
        }
        source = target;
    }

    LOG(INFO) << "Final: " << source;
    /*
    int total = 0;
    for (int i = 0; i < source.size(); i++)
    {
        auto value = -2 + i - origin;
        if (source[i] == '#')
        {
            total += value;
        }
    }
    */
    LOG(INFO) << "Day1: " << source;


}

