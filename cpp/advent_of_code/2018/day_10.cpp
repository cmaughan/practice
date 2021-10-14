#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"
#include <glm/glm.hpp>

using namespace std;

REGISTER_PROBLEM(AOC_2018_Day10)
{
    std::istringstream iss(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_10.txt"));
    std::vector<string> lines;

    for (std::string line; std::getline(iss, line); )
    {
        lines.push_back(line);
    }

    struct point {
        glm::ivec2 pos; glm::ivec2 velocity;
    };
    std::vector<point> pts;

    for (auto& l : lines)
    {
        auto tokens = string_split(l, "=<>, ");
        point pt;
        pt.pos.x = std::stoi(tokens[1]);
        pt.pos.y = std::stoi(tokens[2]);
        pt.velocity.x = std::stoi(tokens[4]);
        pt.velocity.y = std::stoi(tokens[5]);
        pts.push_back(pt);

    }

    int it = 0;
    do
    {
        it++;

        // Get bounds
        auto min = glm::ivec2(std::numeric_limits<int>::max());
        auto max = glm::ivec2(std::numeric_limits<int>::min());
        for (auto& pt : pts)
        {
            pt.pos += pt.velocity;

            min = glm::min(pt.pos, min);
            max = glm::max(pt.pos, max);
        }

        auto size = max - min;
        size = glm::abs(size);
        size += glm::ivec2(1, 1);

        // Arbitrary minimum size to show stuff
        if (size.x < 200 && size.y < 200)
        {
            // Draw the grid into an array
            std::vector<char> grid(size.x * size.y, '.');
            auto get = [&](glm::ivec2& pt)
                -> char&
            {
                return grid[pt.y * size.x + pt.x];
            };
            for (auto& g : grid)
            {
                g = '.';
            }
            for (auto& p : pts)
            {
                get(p.pos - min) = '#';
            }

            std::cout.clear();
            // .. print it
            std::ostringstream str;
            for (int y = 0; y < size.y; y++)
            {
                for (int x = 0; x < size.x; x++)
                {
                    str << get(glm::ivec2(x, y));
                }
                str << std::endl;
            }
            str << "\n" << it << "\n";
            std::cout << str.str();

            // wait for a key
            if (std::cin.get() == 'x')
            break;
        }
    } while (true);
}

