#include "rosalind.h"
#include <queue>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(GRPH)
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

    std::ostringstream strOut;
    
    for (size_t i = 0; i < entries.size(); i++)
    {
        auto pOuter = &entries[i].data[entries[i].data.length() - 3];

        for (size_t ii = 0; ii < entries.size(); ii++)
        {
            if (i == ii)
            {
                continue;
            }

            auto pInner = &entries[i].data[0];

            if (memcmp(pOuter, pInner, sizeof(char) * 3)== 0)
            {
                strOut << entries[i].name << " " << entries[ii].name << std::endl;
            }
        }
    }

    strOut << std::endl;

    WriteOutput(strOut.str());
}


