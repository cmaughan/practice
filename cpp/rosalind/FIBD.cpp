#include "rosalind.h"
#include <queue>
using namespace std;

REGISTER_PROBLEM(FIBD)
{
    std::string text = ReadInput();

    auto args = string_split(text, " ");

    //if (args.size() != 2)
      //  return;

    uint64_t months = std::stol(args[0]); // Months
    uint64_t lifespan = std::stol(args[1]); // Life
    uint64_t pairs = 1;

    unsigned int deadEntries = (unsigned int)(lifespan + 2);
    std::vector<uint64_t> dead(deadEntries, 0);
    unsigned int deadIn = 0;
    unsigned int deadOut = 1;
    dead[deadIn] = 1;

    uint64_t mature, young, result;
    young = 1; // current
    mature = 0; // last
    for (auto gen = 0; gen < months; gen++) 
    {
        deadIn++;
        deadOut++;

        mature = mature - dead[deadOut % deadEntries];

        result = mature + young;

        // Next iteration, young will be remaining mature * pairs
        auto next_young = mature * pairs;

        // Next matures will be current mature + young
        auto next_mature = mature  + young;
                
        // Remember the number of young that will die after dead.size() months.
        dead[deadIn % deadEntries] = next_young;

        // Next iteration
        mature = next_mature;
        young = next_young;
    }

    WriteOutput(std::to_string(result));
}


