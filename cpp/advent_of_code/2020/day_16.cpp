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

class AOC_2020_Day16 : public Object
{
public:
    uint64_t part1;
    uint64_t part2;

    /*departure station: 29-874 or 891-961
    your ticket:
    197,173,229,179,157,83,89,79,193,53,163,59,227,131,199,223,61,181,167,191
    nearby tickets:
    153,109,923,689,426,793,483,628,843,774,785,841,63,168,314,725,489,339,231,914*/

    struct Ranges
    {
        std::pair<int, int> r1;
        std::pair<int, int> r2;
        bool InAnyRange(int i) {
            return (i >= r1.first && i <= r1.second) || (i >= r2.first && i <= r2.second);
        }
        std::set<int> possibleIndices;
    };

    std::unordered_map<std::string, Ranges> mapNameToRanges;
    std::vector<std::string> ruleOrder;

    std::vector<int> ruleValidOrder;
    std::vector<int> myTicket;
    std::vector<std::vector<int>> nearTickets;
    virtual void Read()
    {
        auto str = R"(class: 0-1 or 4-19
row: 0-5 or 8-19
seat: 0-13 or 16-19

your ticket:
11,12,13

nearby tickets:
3,9,18
15,1,5
5,14,9)";

        auto sections = string_split_delim_string(file_read(PRACTICE_ROOT "/advent_of_code/2020/inputs/day_16.txt"), "\r\n\r\n");
        //auto sections = string_split_delim_string(str, "\n\n");

        auto nameRanges = string_split_lines(sections[0]);
        for (auto rangeLine : nameRanges)
        {
            std::regex r = std::regex(R"(([a-z ]+):\s([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+))");
            std::smatch matches;
            if (std::regex_match(rangeLine, matches, r))
            {
                mapNameToRanges[matches[1]].r1 = std::make_pair<int, int>(std::stoi(matches[2]), std::stoi(matches[3]));
                mapNameToRanges[matches[1]].r2 = std::make_pair<int, int>(std::stoi(matches[4]), std::stoi(matches[5]));
                ruleOrder.push_back(matches[1]);
            }
        }

        myTicket = string_get_integers(string_split_lines(sections[1])[1]);

        auto tickets = string_split_lines(sections[2]);
        for (uint32_t ticket = 1; ticket < tickets.size(); ticket++)
        {
            nearTickets.push_back(string_get_integers(tickets[ticket]));
        }

    }
    virtual void RunOnce() override
    {
        Read();

        std::set<int> validTickets;
        {
            PROFILE_SCOPE(Part1);

            part1 = 0;
            for (uint32_t ticketIndex = 0; ticketIndex < nearTickets.size(); ticketIndex++)
            {
                auto& ticket = nearTickets[ticketIndex];

                bool invalid = false;
                // For each ticket slot
                for (uint32_t index = 0; index < ticket.size(); index++)
                {
                    auto& val = ticket[index];

                    // For each rule
                    bool found = false;
                    for (auto& [name, ranges] : mapNameToRanges)
                    {
                        if (ranges.InAnyRange(val))
                        {
                            // Found a rule that this index matches
                            found = true;
                        }
                    }

                    if (!found)
                    {
                        part1 += val;
                        invalid = true;
                    }
                }

                if (!invalid)
                {
                    // This ticket is valid
                    validTickets.insert(ticketIndex);
                }
            }
        }

        {
            PROFILE_SCOPE(Part2);
            part2 = 1;

            // Build all possibilities
            std::map<int, std::set<std::string>> mapIndexToRules;
            for (int i = 0; i < nearTickets[0].size(); i++)
            {
                for (auto& [name, range] : mapNameToRanges)
                {
                    mapIndexToRules[i].insert(name);
                }
            }

            // For every rule
            for (auto& [name, range] : mapNameToRanges)
            {
                // for every index
                for (uint32_t index = 0; index < nearTickets[0].size(); index++)
                {
                    bool absent = false;
                    // in every ticket
                    for (auto& ticketIndex : validTickets)
                    {
                        auto& ticket = nearTickets[ticketIndex];

                        if (!range.InAnyRange(ticket[index]))
                        {
                            absent = true;
                        }
                    }

                    // Rule is missing from one of the tickets for this index, remove it
                    if (absent)
                    {
                        mapIndexToRules[index].erase(name);
                    }
                }
            }

            // Reduce
            bool done = true;
            do
            {
                done = true;
                for (auto& mapRules : mapIndexToRules)
                {
                    // If this rule only has one answer, it is correct; remove from the others
                    if (mapRules.second.size() == 1)
                    {
                        for (auto& mapRules2 : mapIndexToRules)
                        {
                            if (mapRules2.first != mapRules.first)
                            {
                                mapRules2.second.erase(*mapRules.second.begin());
                            }
                        }
                    }
                    else
                    {
                        // Still reduction to do
                        done = false;
                    }
                }
            } while (!done);

            uint64_t count = 1;
            for (uint32_t index = 0; index < myTicket.size(); index++)
            {
                if ((*mapIndexToRules[index].begin()).find("departure") == 0)
                {
                    count *= myTicket[index];
                }
            }
            LOG(DBG, "Part2: " << count);
            part2 = count;
        }
    }

    virtual void DrawGUI() override
    {
        PROFILE_SCOPE(GUI);
        if (ImGui::Begin("Results"))
        {

            ImGui::Text(fmt::format("Part1: {}", part1).c_str());
            ImGui::Text(fmt::format("Part2: {}", part2).c_str());
        }
        ImGui::End();
    }
};


REGISTER_PROBLEM(AOC_2020_Day16)
