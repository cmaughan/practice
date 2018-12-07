#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"
#include <glm/glm.hpp>
#include <set>
#include <deque>

using namespace std;
string test_input(R"(Step C must be finished before step A can begin.
Step C must be finished before step F can begin.
Step A must be finished before step B can begin.
Step A must be finished before step D can begin.
Step B must be finished before step E can begin.
Step D must be finished before step E can begin.
Step F must be finished before step E can begin)");

REGISTER_PROBLEM(AOC_2018_Day7)
{
    std::map<char, std::set<char>> pre_required;
    std::istringstream iss(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_7.txt"));
    std::vector<string> lines;
    for (std::string line; std::getline(iss, line); )
    {
        char word[20];
        char finished[2];
        char next[2];
        sscanf(line.c_str(), "%s %s %s %s %s %s %s %s", word, finished, word, word, word, word, word, next);
        pre_required[next[0]].insert(finished[0]);
    }

    // Walk the pre required, and store all other pre-required
    // Map Char->All Chars before it
    bool added = false;
    do
    {
        added = false;
        for (auto& pre_char : pre_required)
        {
            for (;;)
            {
                std::set<char> keys = pre_char.second;
                for (auto& key : keys)
                {
                    pre_char.second.insert(pre_required[key].begin(), pre_required[key].end());
                }
                if (keys.size() != pre_char.second.size())
                {
                    added = true;
                    continue;
                }
                break;
            }
        }
    } while (added);

    auto walk = [&](int numWorkers, std::map<char, std::set<char>> pre_req)
        -> std::pair<std::string, int>
    {
        int time = 0;
        std::ostringstream str;

        // Remove this character from the pre-required values
        auto remove_requirement = [&](char c)
        {
            for (auto& r : pre_req)
            {
                r.second.erase(c);
            }
            pre_req.erase(c);
        };
    
        // A worker 'thread'
        struct worker
        {
            char c = 0;
            int remaining = 0;
        };
        std::vector<worker> workers(numWorkers);

        // Tick the workers
        auto do_work = [&]()
        {
        };

        std::set<char> assigned;
        do
        {
            // Schedule work
            for (auto& p : pre_req)
            {
                if (pre_req[p.first].empty() && assigned.find(p.first) == assigned.end())
                {
                    auto itr = std::find_if(workers.begin(), workers.end(), [&workers](worker& worker) { return worker.remaining == 0; });
                    if (itr != workers.end())
                    {
                        itr->c = p.first;
                        itr->remaining = itr->c - 'A' + 1 + 60;
                        assigned.insert(itr->c);
                        str << itr->c;
                    }
                }
            }

            // Do work
            time++;

            for (auto& w : workers)
            {
                if (w.remaining > 0)
                {
                    w.remaining--;
                    if (w.remaining == 0)
                    {
                        // Worker done, remove the work packet
                        remove_requirement(w.c);
                        w.c = 0;
                    }
                }
            }

        } while (!pre_req.empty());
        return { str.str(), time };
    };

    auto[str1, time1] = walk(1, pre_required);
    LOG(INFO) << "Part1: " << str1;

    auto[str2, time2] = walk(5, pre_required);
    LOG(INFO) << "Part2: " << time2;
}
