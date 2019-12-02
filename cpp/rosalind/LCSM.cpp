#include "rosalind.h"
#include <queue>
#include <set>
#include <string>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(LCSM)
{
    auto spFasta = ReadInputFasta();
    if (!spFasta)
    {
        return;
    }
    auto& entries = spFasta->GetEntries();
    if (entries.empty())
    {
        LOG(ERROR) << "Not enough entries in fasta table";
        return;
    }
    
    const std::string& firstEntry = entries[0].data;

    std::stringstream out;

    std::set<std::string> found;
    for (size_t i = 0; i < firstEntry.length(); i++)
    {
        for (size_t ii = i + 1; i < firstEntry.length(); i++)
        {
            found.insert(firstEntry.substr(i, ii-i));
            out << firstEntry.substr(i, ii - i) << std::endl;
        }
    }

    out << std::endl;

    WriteOutput(out.str());
}


