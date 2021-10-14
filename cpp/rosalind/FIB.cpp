#include "rosalind.h"

using namespace std;

REGISTER_PROBLEM(FIB)
{
    std::string text = ReadInput();

    auto args = string_split(text, " ");

    if (args.size() != 2)
        return;

    int64_t n = std::stol(args[0]); // Months
    int64_t k = std::stol(args[1]); // Offspring

    int64_t a, b;
    a = 1; // current
    b = 0; // last
    for (auto gen = 1; gen <= n; gen++)
    {
        auto aTemp = a;
        a = a + (k * b); // last * offspring
        b = aTemp;       // last = current
    }

    WriteOutput(std::to_string(b));
}


