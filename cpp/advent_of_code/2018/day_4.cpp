#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"
#include <glm/glm.hpp>
#include <set>
#include "date/include/date/date.h"

using namespace std;
using namespace date;
using namespace chrono;

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
    std::map<int, std::vector<std::tuple<int, int>>> sleep_spans;
    std::map<int, int> sleep_time;
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
            sleep_spans[current_guard].push_back(std::make_tuple(start_time, minute));
            sleep_time[current_guard] += minute - start_time;
        }
    }

    // Get sleepiest
    int longest_sleep = 0;
    int asleep_guard = 0;
    for (auto& g : sleep_time)
    {
        if (g.second > longest_sleep)
        {
            longest_sleep = g.second;
            asleep_guard = g.first;
        }
    }

    struct default_int {
        int count = 0;
    };
    
    std::map<int, default_int> time_to_counts;
    int biggest_time = 0;
    int found_time = 0;
    for (auto& s : sleep_spans[asleep_guard])
    {
        for (auto i = std::get<0>(s); i < std::get<1>(s); i++)
        {
            time_to_counts[i].count++;
            if (time_to_counts[i].count > biggest_time)
            {
                biggest_time = time_to_counts[i].count;
                found_time = i;
            }
        }
    }
    LOG(INFO) << "Part 1: " << asleep_guard * found_time;

    int max_sleep_minute = 0;
    int max_minute = 0;
    int max_sleep_guard = 0;
    for (auto& g : sleep_spans)
    {
        map<int, int> minute_counts;
        auto guard = g.first;
        auto spans = g.second;
        for (auto& s : spans)
        {
            for (auto i = std::get<0>(s); i < std::get<1>(s); i++)
            {
                minute_counts[i]++;
            }
        }

        // Get this guard's best
        int max = 0;
        int minute = 0;
        for (auto& c : minute_counts)
        {
            if (c.second > max)
            {
                max = c.second;
                minute = c.first;
            }
        }

        // Check if this guard beats the others
        if (max > max_sleep_minute)
        {
            max_sleep_minute = max;
            max_sleep_guard = guard;
            max_minute = minute;
        }
    }
    LOG(INFO) << "Part 2: " << max_sleep_guard * max_minute;
}

