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
    std::map<char, std::set<char>> pre_req;
    std::istringstream iss(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_7.txt"));
    std::vector<string> lines;
    for (std::string line; std::getline(iss, line); )
    {
        char word[20];
        char finished[2];
        char next[2];
        sscanf(line.c_str(), "%s %s %s %s %s %s %s %s", word, finished, word, word, word, word, word, next);
        pre_req[next[0]].insert(finished[0]);
    }

    // Walk the pre required, and store all other pre-required
    // Map Char->All Chars before it
    bool added = false;
    do
    {
        added = false;
        for (auto& pre_char : pre_req)
        {
            for (;;)
            {
                std::set<char> keys = pre_char.second;
                for (auto& key : keys)
                {
                    pre_char.second.insert(pre_req[key].begin(), pre_req[key].end());
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

    // Copy for later
    std::map<char, std::set<char>> pre_req2 = pre_req;

    // Remove this character from the pre-required values
    auto remove_requirement = [&](char c)
    {
        for (auto& r : pre_req)
        {
            r.second.erase(c);
        }
        pre_req.erase(c);
    };

    // Find the minimum required character each time and display it.
    std::ostringstream str;
    do
    {
        auto current = pre_req.begin();
        while (current != pre_req.end())
        {
            // Find the first char who's requirements are satisfied
            if (pre_req[current->first].empty())
            {
                str << current->first;
                remove_requirement(current->first);
                current = pre_req.begin();
            }
            else
            {
                current++;
            }
        }
    } while (!pre_req.empty());
    LOG(INFO) << "Part1 : " << str.str();

    // Part 2
    // A worker 'thread'
    struct worker
    {
        char c = 0;
        int remaining = 0;
    };
    std::vector<worker> workers(5);

    // Next empty worker in the pool
    auto find_empty_worker = [&]() -> worker* 
    {
        for (auto& w : workers)
        {
            if (w.remaining == 0)
                return &w;
        }
        return nullptr;
    };

    // Tick the workers
    auto do_work = [&]()
    {
        bool did_work = false;
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
                did_work = true;
            }
        }
        return did_work;
    };

    // Part 2
    std::ostringstream str2;
    int time = 0;
    pre_req = pre_req2;
    std::set<char> assigned;

    do
    {
        // Schedule work
        for (auto& p : pre_req)
        {
            if (pre_req[p.first].empty() && assigned.find(p.first) == assigned.end())
            {
                auto w = find_empty_worker();
                if (w)
                {
                    w->c = p.first;
                    w->remaining = w->c - 'A' + 1 + 60;
                    assigned.insert(w->c);
                }
            }
        }

        // Do work
        time++;
        do_work();
    } while (!pre_req.empty());

    LOG(INFO) << "Part2: " << time;
}
