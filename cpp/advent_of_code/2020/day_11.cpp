#include "common.h"

#include <algorithm>
#include <fstream>
#include <array>
#include <numeric>
#include <regex>
#include <set>
#include <mutils/time/profiler.h>
#include <mutils/math/math.h>
#include <mutils/logger/logger.h>
#include <mutils/string/string_utils.h>

#include <imgui.h>
#include <implot.h>

#include <map>
#include <set>
#include <fmt/format.h>

using namespace std;
using namespace MUtils;

namespace
{
    std::string part1;
    std::string part2;

    class Once
    {
    public:
        Once(std::function<void()> fn)
        {
            fn();
        }
    };
};

#define BEGIN_ONCE static Once once([]()
#define END_ONCE ); 

enum class CellType
{
    Invalid,
    Empty,
    Occupied,
    Floor
};

std::vector<CellType> cells[2];
NVec2i layoutSize;
uint32_t readBuffer = 0;
uint32_t WriteBuffer() { return 1 - readBuffer; };
uint32_t ReadBuffer() { return readBuffer; };
void Swap() { readBuffer = (1 - readBuffer); }

CellType& cell_at(uint32_t buffer, const NVec2i& pos)
{
    if (pos.x < 0 || pos.x >= layoutSize.x || pos.y < 0 || pos.y >= layoutSize.y)
    {
        static CellType invalid = CellType::Invalid;
        return invalid;
    }
    return cells[buffer][layoutSize.y * pos.y + pos.x];
}

uint32_t cell_occupied_adjacent(uint32_t buffer, const NVec2i& pos, bool part1 = true)
{
    // BL, TL, BR, TR, T, B, L, R
    static auto coords = std::array<NVec2i, 8>({ NVec2i{-1, -1}, { -1, 1 }, { 1, 1 }, { 1, -1 }, { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } });
    uint32_t count = 0;
    for (auto i = 0; i < coords.size(); i++)
    {
        auto search = pos;
        for (;;)
        {
            search += coords[i];
            auto cell = cell_at(buffer, search);

            if (cell == CellType::Invalid)
            {
                break;
            }

            if (cell == CellType::Occupied)
            {
                count++;
                break;
            }

            if (!part1 && cell == CellType::Empty)
            {
                break;
            }

            if (part1)
                break;
        }
    }
    return count;
}

void Read()
{
    std::vector<std::string> lines;
    auto in = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_11.txt"));
    layoutSize.x = int(in[0].size());
    layoutSize.y = int(in.size());
    cells[ReadBuffer()].resize(layoutSize.x * layoutSize.y);
    cells[WriteBuffer()].resize(layoutSize.x * layoutSize.y);

    uint32_t cell = 0;
    for (auto& line : in)
    {
        for (auto& ch : line)
        {
            switch (ch)
            {
            case 'L':
                cells[ReadBuffer()][cell++] = CellType::Empty;
                break;
            case '#':
                cells[ReadBuffer()][cell++] = CellType::Occupied;
                break;
            case '.':
                cells[ReadBuffer()][cell++] = CellType::Floor;
                break;
            default:
                assert(!"Invalid input?");
                break;
            }
        }
    }
}

uint32_t DoIt(bool part1, bool& done)
{

    for (auto y = 0; y < layoutSize.x; y++)
    {
        for (auto x = 0; x < layoutSize.x; x++)
        {
            auto pos = NVec2i(x, y);

            auto occ = cell_occupied_adjacent(ReadBuffer(), pos, part1);
            auto& cell = cell_at(ReadBuffer(), pos);
            auto& writeCell = cell_at(WriteBuffer(), pos);

            if ((cell == CellType::Empty) && occ == 0)
            {
                writeCell = CellType::Occupied;
            }
            else if ((cell == CellType::Occupied) && (occ >= (part1 ? 4u : 5u)))
            {
                writeCell = CellType::Empty;
            }
            else
            {
                writeCell = cell;
            }
        }
    }

    uint32_t occ = 0;
    bool stable = true;
    for (auto index = 0; index < cells[ReadBuffer()].size(); index++)
    {
        if (cells[WriteBuffer()][index] != cells[ReadBuffer()][index])
        {
            stable = false;
            //break;
        }

        if (cells[WriteBuffer()][index] == CellType::Occupied)
            occ++;
    }

    if (stable)
    {
        done = true;
    }

    Swap();

    return occ;

}

/*
REGISTER_PROBLEM(AOC_2020_Day11)
{
    PROFILE_SCOPE(Solution);
    PROFILE_SCOPE(ResultPlot);

    static bool read = false;
    if (!read)
    {
        Read();
        read = true;
    }

    bool done;
    //part1 = std::to_string(DoIt(true, done));

    static int counter = 10;
    counter--;

    if (counter <= 0)
    {
        part2 = std::to_string(DoIt(true, done));
        counter = 10;
    }

    if (ImGui::Begin("Results"))
    {
        auto label = std::string(" Occupied: ") + part2;
        ImGui::Text(label.c_str());
        if (ImGui::Button("Reset"))
        {
            read = false;
            readBuffer = 0;
        }
        auto pDrawList = ImGui::GetWindowDrawList();
        auto size = ImGui::GetContentRegionAvail();
        auto pos = ImGui::GetCursorScreenPos();
        auto pixelsPerCellX = size.x / layoutSize.x;
        auto pixelsPerCellY = size.y / layoutSize.y;
        auto minCellSize = (std::min(pixelsPerCellX, pixelsPerCellY));

        for (int y = 0; y < layoutSize.y; y++)
        {
            for (int x = 0; x < layoutSize.x; x++)
            {
                auto cell = cell_at(0, NVec2i(x, y));
                if (cell == CellType::Floor)
                {
                    continue;
                }
               
                float xPixel = pos.x + x * minCellSize;
                float yPixel = pos.y + y * minCellSize;
                if (cell == CellType::Occupied)
                {
                    pDrawList->AddRectFilled(ImVec2(xPixel, yPixel), ImVec2(xPixel + minCellSize, yPixel + minCellSize), ImColor(.6f, .6f, .6f), 6);
                }
                else
                {
                    pDrawList->AddRectFilled(ImVec2(xPixel, yPixel), ImVec2(xPixel + minCellSize, yPixel + minCellSize), ImColor(.2f, .2f, .2f), 6);
                }
            }
        }

        //ImGui::Text(fmt::format("Part1: {}", part1).c_str());
        //ImGui::Text(fmt::format("Part2: {}", part2).c_str());
    }
    ImGui::End();

    static int resetCount = 2;
    if (resetCount == 0)
    {
        Profiler::SetPaused(true);
    }
    resetCount--;
}
*/


