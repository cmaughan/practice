#include "rosalind.h"

using namespace std;

REGISTER_PROBLEM(RNA)
{
    std::string text = ReadInput();

    std::replace(text.begin(), text.end(), 'T', 'U');

    WriteOutput(text);
}


