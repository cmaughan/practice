#pragma once

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include "stringutils.h"
#include "fileutils.h"
#include <chrono>
#include "glm/glm.hpp"
#include "ringitr.h"

#include <cstdio>

template<typename C, typename count, typename Op>
count accumulate_pairs(C& container, count c, Op fun)
{
    for (auto it = container.begin(); it != container.end(); it++)
    {
        for (auto it2 = it + 1; it2 != container.end(); it2++)
        {
            c = fun(c, *it, *it2);
            c = fun(c, *it2, *it);
        }
    }
    return c;
}

static std::vector<int> GetIntegers(const std::string& str)
{
    std::vector<int> vals;
    auto strVals = StringUtils::Split(str, "\t ");
    std::transform(strVals.begin(), strVals.end(), back_inserter(vals), [](const std::string& str) { return stoi(str); });
    return vals;
}

static std::vector<std::vector<int>> GetIntegerGrid(const std::string& str)
{
    // Gather into array
    std::vector<std::string> lines = StringUtils::SplitLines(str);
    std::vector<std::vector<int>> arrayLines;
    for (auto& line : lines)
    {
        std::vector<int> vals;
        auto strVals = StringUtils::Split(line, "\t ");
        std::transform(strVals.begin(), strVals.end(), back_inserter(vals), [](const std::string& str) { return stoi(str); });
        if (!vals.empty())
        {
            arrayLines.push_back(vals);
        }
    }
    return arrayLines;
}

static std::vector<std::vector<std::string>> GetStringGrid(const std::string& str)
{
    // Gather into array
    std::vector<std::string> lines = StringUtils::SplitLines(str);
    std::vector<std::vector<std::string>> arrayLines;
    for (auto& line : lines)
    {
        std::vector<std::string> vals = StringUtils::Split(line, "\t ");
        if (!vals.empty())
        {
            arrayLines.push_back(vals);
        }
    }
    return arrayLines;
}

class Timer
{
public:
    Timer(const std::string& strName)
        : m_strName(strName)
    {
        start = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

    void Stop()
    {
        if (!finished)
        {
            auto now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            std::cout << m_strName << ": " << (now - start) << "us" << std::endl;
            finished = true;
        }
    }

    ~Timer()
    {
        Stop();
    }
private:
    bool finished = false;
    int64_t start;
    int64_t now;
    std::string m_strName;
};

inline glm::ivec2 UlamIndexToCoords(int n)
{
    const auto k = std::ceil((std::sqrt(n) - 1) / 2);
    auto t = 2 * k + 1;
    auto m = std::pow(t, 2);

    t -= 1;

    if (n >= m - t)
    {
        return glm::ivec2(k - (m - n), -k);
    }

    m -= t;

    if (n >= m - t) {
        return glm::ivec2(-k, -k + (m - n));
    }

    m -= t;

    if (n >= m - t)
    {
        return glm::ivec2(-k + (m - n), k);
    }

    return glm::ivec2(k, k - (m - n - t));
};

