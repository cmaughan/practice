#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"
#include <glm/glm.hpp>

using namespace std;

REGISTER_PROBLEM(AOC_2018_Day3)
{
    struct cut {
        int id;
        glm::ivec2 coord;
        glm::ivec2 size;
    };

    // Split so I just have id,x,y,dx,dy
    std::vector<cut> cuts;
    auto input = string_split(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_3.txt"), " \t\r\n#@:,:x");

    // Find biggest rect as I go
    glm::ivec2 max_rect(0);
    auto itr = input.begin();
    while (itr != input.end())
    {
        // Fill a struct with the integer values
        cut c;
        c.id = std::stoi(*itr++);
        c.coord.x = std::stoi(*itr++);
        c.coord.y = std::stoi(*itr++);
        c.size.x = std::stoi(*itr++);
        c.size.y = std::stoi(*itr++);
        cuts.push_back(c);

        // Find the max rectangle size
        max_rect.x = std::max(max_rect.x, (c.coord + c.size).x);
        max_rect.y = std::max(max_rect.y, (c.coord + c.size).y);
    }

    // Make the cloth
    std::vector<int> cloth(max_rect.x * max_rect.y, 0);

    // Walk a cloth piece, returning a ref to the value in that cloth coord
    auto walk_cloth_piece = [&](auto coord, auto size, auto fn)
    {
        auto bottom_right = coord + size;
        for (int x = coord.x; x < bottom_right.x; x++)
        {
            for (int y = coord.y; y < bottom_right.y; y++)
            {
                fn(cloth[x + y * max_rect.x]);
            }
        }
    };

    // Fill the areas
    for (auto& c : cuts)
    {
        walk_cloth_piece(c.coord, c.size, [](int& val) { val++; });
    }

    // count the covered squares
    LOG(INFO) << "Part 1: " << std::count_if(cloth.begin(), cloth.end(), [](int val) { return val > 1; });

    // Part 2, find the piece on its own
    for (auto& c : cuts)
    {
        bool found = true;
        walk_cloth_piece(c.coord, c.size, [&found](int& val) { if (val > 1) found = false; });

        if (found)
        {
            LOG(INFO) << "Part 2: " << c.id;
            break;
        }
    }
}
