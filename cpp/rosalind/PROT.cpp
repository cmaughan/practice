#include "rosalind.h"

using namespace std;

REGISTER_PROBLEM(PROT)
{
    std::string text = ReadInput();

    // Create a codon mapper
    Codon codonMapper;

    std::ostringstream strOut;

    auto groups = text.size() / 3;
    for (auto group = 0; group < groups; group++)
    {
        std::string result = codonMapper.Map(text.substr(group * 3, 3));
        if (result.empty())
        {
            // We are done, or didn't recognize
            break;
        }

        strOut << result;
    }

    WriteOutput(strOut.str());
}


