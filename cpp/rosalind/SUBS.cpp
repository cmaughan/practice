#include "rosalind.h"

using namespace std;

REGISTER_PROBLEM(SUBS)
{
    std::string text = ReadInput();
    auto split = string_split(text, "\n");
    if (split.size() < 2)
    {
        assert("Not valid");
        return;
    }
    const auto& search = split[0];
    const auto& data = split[1];

    // Search
    std::ostringstream output;
    std::string::size_type pos = 0;
    while ((pos = data.find(search, pos)) != std::string::npos)
    {
        output << (pos) << " ";
        pos++;
    }
    WriteOutput(output.str());
}


