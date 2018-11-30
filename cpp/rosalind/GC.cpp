#include "rosalind.h"

#include <algorithm>

using namespace std;

REGISTER_PROBLEM(GC)
{
    auto spFasta = ReadInputFasta();

    int biggest = -1;
    float maxPercent = std::numeric_limits<float>::min();

    const auto& entries = spFasta->GetEntries();
    for (int i = 0; i < int(entries.size()); i++)
    {
        auto countGC = std::count(entries[i].data.begin(), entries[i].data.end(), 'G') +
            std::count(entries[i].data.begin(), entries[i].data.end(), 'C');
        float percent = float(countGC) / float(entries[i].data.size()) * 100.0f;
        if (maxPercent < percent)
        {
            maxPercent = percent;
            biggest = i;
        }
    }

    if (biggest != -1)
    {
        std::ostringstream str;
        str << entries[biggest].name << std::endl << maxPercent << std::endl;
        WriteOutput(str.str());
    }
}


