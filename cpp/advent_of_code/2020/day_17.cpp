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

#include <unordered_map>
#include <set>
#include <fmt/format.h>

using namespace std;
using namespace MUtils;

namespace std
{
    template<>
    struct hash<NVec4i>
    {
        std::size_t operator()(const NVec4i& k) const
        {
            return (k.w << 21) | (k.z << 14) | (k.y << 7) | (k.x);
        }
    };
}

class AOC_2020_Day17 : public Object
{
public:
    uint64_t part1;
    uint64_t part2;

    enum class CellType
    {
        Active,
        Inactive,
        Invalid
    };

    struct Cell
    {
        CellType type = CellType::Inactive;
    };
    std::unordered_map<NVec4i, Cell> cells[2];
    NVec4i max;
    NVec4i min;
    bool read = true;
    uint32_t readBuffer = 0;
    uint32_t iterations = 0;
    uint32_t WriteBuffer() { return 1 - readBuffer; };
    uint32_t ReadBuffer() { return readBuffer; };
    void Swap() { readBuffer = (1 - readBuffer); }

    uint32_t cell_occupied_adjacent(uint32_t buffer, const NVec4i& pos)
    {
        int count = 0;
        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                for (int z = -1; z <= 1; z++)
                {
                    for (int w = -1; w <= 1; w++)
                    {
                        if ((x == 0) && (y == 0) && (z == 0) && (w == 0))
                        {
                            continue;
                        }

                        auto search = pos + NVec4i(x, y, z, w);
                        auto cell = cells[buffer][search];
                        if (cell.type == CellType::Active)
                        {
                            count++;
                        }
                    }
                }
            }
        }
        return count;
    }

    virtual void Read()
    {
        auto in = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_17.txt"));
        auto str = R"(.#.
..#
###)";
        //in = string_split_lines(str);

        uint32_t cell = 0;
        NVec4i coord = NVec4i(0, 0, 0, 0);
        for (auto& line : in)
        {
            for (auto& ch : line)
            {
                switch (ch)
                {
                case '#':
                    cells[ReadBuffer()][coord].type = CellType::Active;
                    break;
                case '.':
                    cells[ReadBuffer()][coord].type = CellType::Inactive;
                    break;
                default:
                    assert(!"Invalid input?");
                    break;
                }
                coord.x++;
            }
            coord.y++;
            coord.x = 0;
        }
        max.x = int(in[0].size());
        max.y = int(in.size());
        max.z = 1;
        max.w = 1;

        min = NVec4i(-1, -1, -1, -1);
    }

    virtual void Run() override
    {
        if (read)
        {
            Read();
            read = false;
            iterations = 0;
        }

        auto Run = [&]()
        {
            for (int x = min.x; x <= max.x; x++)
            {
                for (int y = min.y; y <= max.y; y++)
                {
                    for (int z = min.z; z <= max.z; z++)
                    {
                        for (int w = min.w; w <= max.w; w++)
                        {
                            auto pos = NVec4i(x, y, z, w);
                            auto cell = cells[ReadBuffer()][pos];

                            auto occ = cell_occupied_adjacent(ReadBuffer(), pos);
                            auto& writeCell = cells[WriteBuffer()][pos];

                            if (cell.type == CellType::Active)
                            {
                                if (occ == 2 || occ == 3)
                                {
                                    writeCell.type = CellType::Active;
                                }
                                else
                                {
                                    writeCell.type = CellType::Inactive;
                                }
                            }
                            else if (cell.type == CellType::Inactive)
                            {
                                if (occ == 3)
                                {
                                    writeCell.type = CellType::Active;
                                }
                                else
                                {
                                    writeCell.type = CellType::Inactive;
                                }
                            }
                        }
                    }
                }
            }
            Swap();

            max += NVec4i(1);
            min -= NVec4i(1);
        };

        //for (int i = 0; i < 6; i++)
        {
            if (iterations < 5)
            {
                Run();
                iterations++;
            }

        }

        part1 = 0;
        /*
        for (auto& [pos, cell] : cells[ReadBuffer()])
        {
            if (cell.type == CellType::Active)
                part1++;
        }
        */
    }

    virtual void DrawGUI() override
    {
        PROFILE_SCOPE(GUI);
        if (ImGui::Begin("Results"))
        {
            auto label = std::string(" Occupied: ") + std::to_string(part1);
            ImGui::Text(label.c_str());
            if (ImGui::Button("Reset"))
            {
                read = false;
                readBuffer = 0;
            }

            auto xSize = max.x - min.x;
            auto ySize = max.y - min.y;
            auto zSize = max.z - min.z;
            auto wSize = max.w - min.w;
            auto pDrawList = ImGui::GetWindowDrawList();
            auto size = ImGui::GetContentRegionAvail();
            auto pos = ImGui::GetCursorScreenPos();
            auto pixelsPerCellX = size.x / (xSize);
            auto pixelsPerCellY = size.y / (ySize);
            auto minCellSize = (std::min(pixelsPerCellX, pixelsPerCellY));

            auto zY = zSize / 2;
            auto zX = zSize / zY;
            auto subCellSizeY =  minCellSize / zY;
            auto subCellSizeX =  minCellSize / zX;

            auto wY = wSize / 2;
            auto wX = wSize / wY;
            auto wCellSizeY =  subCellSizeY / wY;
            auto wCellSizeX =  subCellSizeX / wX;

            for (int x = 0; x < xSize; x++)
            {
                for (int y = 0; y < ySize; y++)
                {
                    float xPixelX = pos.x + x * minCellSize;
                    float yPixelY = pos.y + y * minCellSize;
                    //pDrawList->AddRectFilled(ImVec2(xPixelX, yPixelY), ImVec2(xPixelX + minCellSize, yPixelY + minCellSize), ImColor(.1f, .02f, .02f), 20);
                 
                    for (int z = 0; z < zSize; z++)
                    {
                        for (int w = 0; w < wSize; w++)
                        {
                            auto cell = cells[0][NVec4i(x + min.x, y + min.y, z + min.z, w + min.w)];

                            float xPixel = pos.x + x * minCellSize;
                            float yPixel = pos.y + y * minCellSize;

                            auto ySub = z / zY;
                            auto xSub = z % zY;
                            xPixel += (ySub * subCellSizeX);
                            yPixel += (xSub * subCellSizeY);

                            auto ySubW = w / wY;
                            auto xSubW = w % wY;
                            xPixel += (ySubW * wCellSizeX);
                            yPixel += (xSubW * wCellSizeY);

                            if (cell.type == CellType::Active)
                            {
                                pDrawList->AddRectFilled(ImVec2(xPixel, yPixel), ImVec2(xPixel + wCellSizeX, yPixel + wCellSizeY), ImColor(.6f, .6f, .6f), 2);
                            }
                            else
                            {
                                pDrawList->AddRectFilled(ImVec2(xPixel, yPixel), ImVec2(xPixel + wCellSizeX, yPixel + wCellSizeY), ImColor(.2f, .2f, .2f), 2);
                            }
                        }
                    }
                }
            }

            //ImGui::Text(fmt::format("Part1: {}", part1).c_str());
            //ImGui::Text(fmt::format("Part2: {}", part2).c_str());
            ImGui::End();
        }
    }
};


REGISTER_PROBLEM(AOC_2020_Day17)
