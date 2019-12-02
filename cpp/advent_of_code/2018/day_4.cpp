#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"
#include <glm/glm.hpp>
#include <set>

using namespace std;
using namespace chrono;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2018_Day4)
{
    std::istringstream iss(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/day_4.txt"));
    std::vector<string> lines;
    for (std::string line; std::getline(iss, line); )
    {
        lines.push_back(line);
    }
    std::sort(lines.begin(), lines.end());

    int current_guard;
    int start_time;
    std::map<int, int> sleep_time;
    std::map<int, std::map<int, int>> guard_to_minute_counts;
    for (auto& l : lines)
    {
        int year, hour, month, day, minute;
        char word1[50];
        char word2[50];
        sscanf(l.c_str(), "[%d-%d-%d %d:%d] %s %s", &year, &month, &day, &hour, &minute, word1, word2);

        if (strcmp(word1, "Guard") == 0)
        {
            // Awake at this time
            current_guard = std::stoi(std::string(&word2[1]));
        }
        else if (strcmp(word1, "falls") == 0)
        {
            start_time = minute;
        }
        else
        {
            sleep_time[minute - start_time] = current_guard;
            for (int i = start_time; i < minute; i++)
            {
                guard_to_minute_counts[current_guard][i]++;
            }
        }
    }

    auto asleep_guard = sleep_time.rbegin()->second;
    auto itr = std::max_element(guard_to_minute_counts[asleep_guard].begin(), guard_to_minute_counts[asleep_guard].end(), [](auto v1, auto v2)
    {
        return v1.second < v2.second;
    });

    LOG(INFO) << "Part 1: " << asleep_guard * itr->first;

    int max_sleep_minute = 0;
    int max_minute = 0;
    int max_sleep_guard = 0;
    for (auto& g : guard_to_minute_counts)
    {
        auto itr = std::max_element(g.second.begin(), g.second.end(), [](auto v1, auto v2)
        {
            return v1.second < v2.second;
        });

        // Check if this guard beats the others
        if (itr->second > max_sleep_minute)
        {
            max_sleep_minute = itr->second;
            max_sleep_guard = g.first;
            max_minute = itr->first;
        }
    }
    LOG(INFO) << "Part 2: " << max_sleep_guard * max_minute;
}

