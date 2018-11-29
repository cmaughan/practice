#include "common.h"
#include "utils.h"
#include "stringutils.h"

#include <chrono>

// Timer class
Timer::Timer(const std::string& strName)
    : m_strName(strName)
{
    start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    LOG(INFO) << m_strName << ": Started";
}

void Timer::Stop()
{
    if (!finished)
    {
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        LOG(INFO) << m_strName << ": " << (now - start) << " ms";
        finished = true;
    }
}

Timer::~Timer()
{
    Stop();
}

std::vector<std::vector<std::string>> utils_get_string_grid(const std::string& str)
{
    // Gather into array
    std::vector<std::string> lines = string_split_lines(str);
    std::vector<std::vector<std::string>> arrayLines;
    for (auto& line : lines)
    {
        std::vector<std::string> vals = string_split(line, "\t ");
        if (!vals.empty())
        {
            arrayLines.push_back(vals);
        }
    }
    return arrayLines;
}

std::vector<std::vector<int>> utils_get_integer_grid(const std::string& str)
{
    // Gather into array
    std::vector<std::string> lines = string_split_lines(str);
    std::vector<std::vector<int>> arrayLines;
    for (auto& line : lines)
    {
        std::vector<int> vals;
        auto strVals = string_split(line, "\t ");
        std::transform(strVals.begin(), strVals.end(), back_inserter(vals), [](const std::string& str) { return stoi(str); });
        if (!vals.empty())
        {
            arrayLines.push_back(vals);
        }
    }
    return arrayLines;
}

std::vector<int> utils_get_integers(const std::string& str)
{
    std::vector<int> vals;
    auto strVals = string_split(str, "\t ");
    std::transform(strVals.begin(), strVals.end(), back_inserter(vals), [](const std::string& str) { return stoi(str); });
    return vals;
}


