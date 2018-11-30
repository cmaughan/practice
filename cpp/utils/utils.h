#pragma once

template<typename C, typename count, typename Op>
count accumulate_pairs(C& container, count c, Op fun)
{
    for (auto it = container.begin(); it != container.end(); it++)
    {
        for (auto it2 = it + 1; it2 != container.end(); it2++)
        {
            // Think I intended to add these?
            c = fun(c, *it, *it2);
            c = fun(c, *it2, *it);
        }
    }
    return c;
}

std::vector<int> utils_get_integers(const std::string& str);
std::vector<std::vector<int>> utils_get_integer_grid(const std::string& str);
std::vector<std::vector<std::string>> utils_get_string_grid(const std::string& str);

class Timer
{
public:
    Timer(const std::string& strName);
    ~Timer();

    void Stop();
private:
    bool finished = false;
    int64_t start;
    int64_t now;
    std::string m_strName;
};


