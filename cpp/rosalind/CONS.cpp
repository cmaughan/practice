#include "rosalind.h"

#include "Fasta.h"
#include <assert.h>
#include <bitset>
#include <vector>

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(CONS)
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

    // Internal ordering, using bit fiddling for array indices
    const int A = 0;
    const int C = 1;
    const int T = 2;
    const int G = 3;

    // From nucleotide to 0->4
    #define N_TO_INDEX(n) ((n >> 1) & 0x3)

    // From 0->4 to nucleotide
    char mapChar[4]{ 'A', 'C', 'T', 'G' };

    std::vector<int[4]> counts(entries[0].data.length());
    memset(counts[0], 0, counts.size() * sizeof(int) * 4);

    for (auto& entry : entries)
    {
        for (std::size_t i = 0; i < counts.size(); i++)
        {
            counts[i][N_TO_INDEX(entry.data[i])]++;
        }
    }

    std::ostringstream outputCons;

    std::ostringstream outputCounts[4];
    outputCounts[A] << "A: ";
    outputCounts[C] << "C: ";
    outputCounts[G] << "G: ";
    outputCounts[T] << "T: ";

    for (std::size_t i = 0; i < counts.size(); i++)
    {
        int max = -1;
        int found = -1;
        for (int compare = 0; compare < 4; compare++)
        {
            outputCounts[compare] << counts[i][compare] << " ";

            if (counts[i][compare] > max)
            {
                max = counts[i][compare];
                found = compare;
            }
        }
    
        outputCons << mapChar[found];
    }

    // External ordering (ACGT)
    int outputMap[4]{ 0, 1, 3, 2 };

    outputCons << std::endl;
    WriteOutput(outputCons.str());

    for (int i = 0; i < 4; i++)
    {
        outputCounts[outputMap[i]] << std::endl;
        WriteOutput(outputCounts[outputMap[i]].str());
    }
    
}


