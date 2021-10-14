#include "rosalind.h"

using namespace std;

REGISTER_PROBLEM(IPRB)
{
    std::string text = ReadInput();
    auto split = string_split(text, " ");
    if (split.size() < 3)
    {
        assert("Not valid");
        return;
    }

    const float& YY = std::stof(split[0]); // Homozygous Dom       YY
    const float& Yy = std::stof(split[1]); // Heterozygous         Yy
    const float& yy = std::stof(split[2]); // Homozygous Recessive yy
    
    float total = YY + Yy + yy;

    // Yy * yy
    // Probability of a Heterozygous mating with a Homozygous recessive.
    float Yyyy = ((Yy / total) * (yy / (total - 1))) +
                 ((yy / total) * (Yy / (total - 1)));

    // yy * yy
    // Homozygous recessive
    float yyyy = (yy / total) * ((yy - 1) / (total - 1));

    // Yy * Yy
    // Heterozygous
    float YyYy = (Yy / total) * ((Yy - 1) / (total - 1));
    
    float recessive = (Yyyy * .5f) + yyyy + (YyYy * .25f);
    float prob = 1.0f - recessive;
    WriteOutput(std::to_string(prob));
}


