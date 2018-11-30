#include "rosalind.h"
#include <algorithm>

using namespace std;

REGISTER_PROBLEM(HAMM)
{
    std::string text = ReadInput();
    auto split = string_split(text, "\n");
    if (split.size() < 2)
    {
        assert("Not valid");
        return;
    }

    const auto& string1 = split[0];
    const auto& string2 = split[1];
    auto size = std::min(string1.length(), string2.length());
    
    unsigned int distance = 0;
    for (int index = 0; index < size; index++)
    {
        if (string1[index] != string2[index])
        {
            distance++;
        }
    }
    WriteOutput(std::to_string(distance));
}


