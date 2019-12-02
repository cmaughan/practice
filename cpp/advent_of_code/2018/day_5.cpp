#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"
#include <glm/glm.hpp>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2018_Day5)
{
    auto text = file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_5.txt");
    //auto input = std::string("dabAcCaCBAcCcaDA");
    char diff = std::abs('A' - 'a');

    auto process = [&](std::string& input)
    {
        int index = 0;
        while (index < input.size())
        {
            if (index > 0)
            {
                auto char_diff = std::abs(input[index] - input[index - 1]);
                if (char_diff == diff)
                {
                    input.erase(input.begin() + index - 1, input.begin() + index + 1);
                    index -= 1;
                    index = std::max(0, index);
                    continue;
                }
            }
            index++;
        }
    };
    process(text);
    
    LOG(INFO) << "Part 1: " << text.size();


    auto input2 = file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_5.txt");
    char best;
    auto best_size = std::numeric_limits<int>::max();
    std::map<char, std::string> results;
    for (char c = 'A'; c <= 'Z'; c++)
    {
        std::string output = input2;
        output.erase(std::remove_if(output.begin(), output.end(), [diff,c](auto ch) { return ch == c || ch == (c + diff); }), output.end());

        process(output);
        if (output.length() < best_size)
        {
            results[c] = output;
            best_size = (int)output.length();
            best = c;
        }
    }

    LOG(INFO) << "Part 2: " << results[best].size();

}

