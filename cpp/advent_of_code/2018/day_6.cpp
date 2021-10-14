#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"
#include <glm/glm.hpp>
#include <algorithm>

using namespace std;
using namespace MUtils;

auto sample_input = std::string(R"(1, 1
1, 6
8, 3
3, 4
5, 5
8, 9)");

REGISTER_PROBLEM(AOC_2018_Day6)
{
    Timer t("Part1: ");
    std::vector<glm::ivec2> coords;
    glm::ivec2 size(0);
    auto input = utils_get_integer_grid(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_6.txt"));
    for (auto& row : input)
    {
        coords.push_back(glm::ivec2(row[0], row[1]));
        size.x = std::max(size.x, row[0] + 1);
        size.y = std::max(size.y, row[1] + 1);
    }

    struct Cell { int distance = std::numeric_limits<int>::max(); int owner = -1; };
    std::vector<Cell> cells(size.x * size.y);

    auto get_cell = [&](int x, int y) -> Cell& { return cells[y * size.x + x]; };
    for (int owner = 0; owner < coords.size(); owner++)
    {
        auto coord = coords[owner];
        for (int x = 0; x < size.x; x++)
        {
            for (int y = 0; y < size.y; y++)
            {
                auto& cell = get_cell(x, y);
                int manhatten = std::abs(coord.x - x) + std::abs(coord.y - y);
                if (manhatten < cell.distance)
                {
                    cell.distance = manhatten;
                    cell.owner = owner;
                }
                if (manhatten == cell.distance && cell.owner != owner)
                {
                    cell.owner = -1;
                }
            }
        }
    }

    // Print the grid!
    /*
    std::ostringstream str;
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            auto cell = get_cell(x, y);
            if (cell.owner == -1)
            {
                str << ".";
            }
            else
            {
                str << (char)(cell.owner + 'A');
            }
        }
        str << std::endl;
    }
    std::cout << str.str();
    */

    std::map<int, int> owner_counts;
    for (int i = 0; i < coords.size(); i++)
    {
        owner_counts[i] = 0;
    }

    for (int x = 0; x < size.x; x++)
    {
        for (int y = 0; y < size.y; y++)
        {
            auto& cell = get_cell(x, y);
            if (owner_counts.find(cell.owner) != owner_counts.end())
            {
                if (x == 0 || y == 0 || x == (size.x - 1) || y == (size.y - 1))
                {
                    // Remove if seen at the boundary
                    if (cell.owner != -1)
                    {
                        owner_counts.erase(cell.owner);
                    }
                }
                else
                {
                    owner_counts[cell.owner]++;
                }
            }
        }
    }

    int max = 0;
    int id = -1;
    for (auto& m : owner_counts)
    {
        if (m.second > max)
        {
            max = m.second;
            id = m.first;
        }
    }
    t.Stop();

    LOG(INFO) << "Part 1: " << max;
    Timer t2("Part2 : ");

    // Find the distances < 10000
    int under = 0;
    const int max_size = 200;
    const int compare = 10000;
    for (int x = -max_size - size.x; x < max_size + size.x; x++)
    {
        for (int y = -max_size; y < size.y + max_size; y++)
        {
            int total = 0;
            for (int owner = 0; owner < coords.size(); owner++)
            {
                auto coord = coords[owner];
                total += std::abs(coord.x - x) + std::abs(coord.y - y);
                if (total >= compare)
                    break;
            }
            if (total < compare)
            {
                under++;
            }
        }
    }

    LOG(INFO) << "Part 2: " << under;
}

