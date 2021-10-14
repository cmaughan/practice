#include "rosalind.h"

#include <crtdbg.h>
#include <cassert>
#include "stringutils.h"


#include "KUtils.h"
using namespace std;

REGISTER_PROBLEM(CLUMPS)
{
    std::string text = ReadInput();
    auto split = string_split(text, "\n");
    if (split.size() < 2)
    {
        assert("Not valid");
        return;
    }
    std::string input = split[0];

    auto params = string_split(split[1], " ");
    uint32_t kMerLength = std::stoi(params[0]);
    uint32_t LWindow = std::stoi(params[1]);
    uint32_t tFrequency = std::stoi(params[2]);

    auto frequencyTable = KMer_MakeFrequencyTable<uint32_t>(kMerLength);

    std::ostringstream strOut;
    std::string val;

    std::set<uint32_t> foundClumps;
    std::set<uint32_t> clumps;
    auto checkClumps = [&]()
    {
        for (auto clump : clumps)
        {
            if (foundClumps.find(clump) == foundClumps.end())
            {
                foundClumps.insert(clump);
                KMer_FromHash<uint32_t>(val, clump, kMerLength);
                strOut << val << " ";
            }
        }
    };

    KMer_PopulateFrequencyTable<uint32_t>(frequencyTable, clumps, tFrequency, input.c_str(), LWindow, kMerLength);
    checkClumps();
    
    for (uint32_t index = 1; index < input.length() - LWindow; index++)
    {
        //ABCD ABC BCD // Remove Ak, Add index + Winsize - 1 
        KMer_UpdateFrequencyTable<uint32_t>(frequencyTable, clumps, tFrequency, &input[index], &input[index + LWindow - kMerLength - 1], kMerLength);
        checkClumps();
    }
   
    strOut << std::endl;
    WriteOutput(strOut.str());
}