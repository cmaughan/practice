#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"
#include <glm/glm.hpp>
#include <set>
#include <deque>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2018_Day7)
{
    std::map<char, std::set<char>> pre_required;
    std::istringstream iss(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_7.txt"));
    std::vector<string> lines;
    for (std::string line; std::getline(iss, line); )
    {
        auto vals = std::make_pair( line[5], line[36] );
        pre_required[vals.second].insert(vals.first);
        if (pre_required.find(vals.first) == pre_required.end())
        {
            pre_required[vals.first] = {};
        }
    }

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
        struct worker { char c = 0; int remaining = 0; };
        std::vector<worker> workers(numWorkers);

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
