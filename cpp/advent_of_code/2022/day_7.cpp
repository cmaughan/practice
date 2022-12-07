#include "common.h"

#include <algorithm>
#include <deque>
#include <mutils/time/profiler.h>
#include <mutils/algorithm/container_utils.h>
#include <numeric>
#include <set>

#include <imgui.h>

#include <fmt/format.h>

using namespace std;
using namespace MUtils;

namespace
{
int64_t part1;
int64_t part2;
std::ostringstream str;
} // namespace

struct file
{
    int64_t size = 0;
    std::string name;
};


struct folder
{
    std::vector<folder> children;
    folder* pParent = nullptr;
    std::string name;
    std::int64_t localFileSize = 0;
    std::int64_t allChildrenSize = 0;
    std::vector<file> files;
};

void indent(std::ostringstream& str, uint32_t indent)
{
    for (uint32_t i = 0; i < indent; i++)
    {
        str << " ";
    }
}

void print_file(std::ostringstream& str, file* pFolder)
{
    str << pFolder->name << " " << pFolder->size << std::endl;
}

void print_folder(std::ostringstream& str, folder* pFolder, uint32_t i)
{
    indent(str, i);
    str << pFolder->name << " (" << pFolder->allChildrenSize << ")" << std::endl;
    for (auto& file : pFolder->files)
    {
        indent(str, i + 4);
        print_file(str, &file);
    }
}

class AOC_2022_Day7 : public Object
{
    /*virtual void RunOnce() override
    {
        PROFILE_SCOPE(Solution);

        folder root;
        root.name = "/";
        root.pParent = nullptr;
        folder* pCurrent = &root;

        auto getFolder = [&](auto& parent, auto name) -> folder* {
            auto itr = std::find_if(parent.children.begin(), parent.children.end(), [&](auto entry) { return entry.name == name; });
            if (itr != parent.children.end())
                return &(*itr);
            return (folder*)nullptr;
        };

        auto addFolder = [&](auto& parent, auto name) {
            auto pFound = getFolder(parent, name);
            if (pFound)
            {
                return pFound;
            }
            folder f;
            f.name = name;
            f.pParent = &parent;
            parent.children.push_back(f);
            return &parent.children.back();
        };

        // Building tree
        auto input = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2022/inputs/day_7.txt"));
        for (auto row : input)
        {
            auto values = string_split(row, " ");
            if (values[0][0] == '$')
            {
                // Ignore ls
                if (values[1][0] == 'c')
                {
                    if (values[2][0] == '/')
                    {
                        pCurrent = &root;
                    }
                    else if (values[2][0] == '.')
                    {
                        if (pCurrent->pParent)
                        {
                            pCurrent = pCurrent->pParent;
                        }
                    }
                    else
                    {
                        // cd here
                        pCurrent = addFolder(*pCurrent, values[2]);
                    }
                }
            }
            else
            {
                if (values[0][0] == 'd')
                {
                    addFolder(*pCurrent, values[1]);
                }
                else
                {
                    auto file_size = std::stoull(values[0]);
                    pCurrent->files.push_back(file{ file_size, values[1] });
                    pCurrent->localFileSize += file_size;
                }
            }
        }

        // Build all the child file sizes into each folder
        using fnBuildSizes = std::function<uint64_t(folder*)>;
        fnBuildSizes all = [&](auto pFolder) {
            pFolder->allChildrenSize += pFolder->localFileSize;
            for (auto& child : pFolder->children)
            {
                pFolder->allChildrenSize += all(&child);
            }
            return pFolder->allChildrenSize;
        };

        // What we need for part 2
        auto used = all(&root);
        auto free = 70000000 - used;
        auto required = 30000000 - free;

        uint64_t small_ones = 0;
        uint64_t nearest_dist = std::numeric_limits<uint64_t>::max();
        folder* pDeleteFolder = nullptr;

        using fnSearch = std::function<void(folder*, uint32_t indent)>;
        fnSearch finder = [&](auto pFolder, uint32_t indent) {

            print_folder(str, pFolder, indent);

            if (pFolder->allChildrenSize <= 100000)
            {
                small_ones += pFolder->allChildrenSize;
            }

            if (pFolder->allChildrenSize >= required)
            {
                auto dist =  pFolder->allChildrenSize - required;
                if (dist < nearest_dist)
                {
                    pDeleteFolder = pFolder;
                    nearest_dist = dist;
                }
            }

            auto dist = pFolder->allChildrenSize;
            for (auto& child : pFolder->children)
            {
                finder(&child, indent + 4);
            }
        };

        finder(&root, 0);
        part1 = small_ones;
        part2 = pDeleteFolder->allChildrenSize;
    }
    */

    virtual void RunOnce() override
    {
        auto input = string_split_lines(file_read(PRACTICE_ROOT "/advent_of_code/2022/inputs/day_7.txt"));

        std::vector<std::string> folders = { "/" };
        std::map<std::string, int64_t> sizes;
        for (auto row : input)
        {
            auto values = string_split(row, " ");
            if (values[0] == "$" && values[1] == "cd")
            {
                switch (values[2][0])
                {
                case '.':
                    if (!folders.empty())
                    {
                        folders.pop_back();
                    }
                    break;
                case '/':
                    folders.clear(); // Fall through
                default:
                    folders.push_back(values[2]);
                    break;
                }
            }
            else
            {
                if (values[0] != "$" && values[0][0] != 'd')
                {
                    std::ostringstream key;
                    for (auto& str : folders)
                    {
                        key << str;
                        sizes[key.str()] += std::stoull(values[0]);
                    }
                }
            }
        }

        // Add all <= 100000
        part1 = std::accumulate(sizes.begin(), sizes.end(), 0ll, [](auto current_total, auto pr) {
            if (pr.second <= 100000)
            {
                return current_total + pr.second;
            }
            return current_total;
        });

        // Find all big enough to make room, sorted into a set
        const auto required = 30000000 - (70000000 - sizes["/"]);
        auto filtered = filter_map_to_set(sizes, [&](auto val) {
            return (val.second >= required);
        });

        part2 = *filtered.begin();
    }

    virtual void DrawGUI() override
    {
        PROFILE_SCOPE(ResultPlot);
        if (ImGui::Begin(GetName().c_str()))
        {
            ImGui::Text(fmt::format("Part1: {}", part1).c_str());
            ImGui::Text(fmt::format("Part2: {}", part2).c_str());
            ImGui::Text(str.str().c_str());
        }
        ImGui::End();
    }
};

REGISTER_PROBLEM(AOC_2022_Day7);
