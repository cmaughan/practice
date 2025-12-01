#include <filesystem>
#include <fstream>
#include <iostream>

#include <Zest/file/file.h>
#include <Zest/logger/logger.h>
#include <Zest/string/string_utils.h>

#include "config_app.h"

using namespace Zest;

namespace Zest
{
#undef ERROR
#ifdef _DEBUG
Logger logger = { true, LT::DBG };
#else
Logger logger = { true, LT::INFO };
#endif
bool Log::disabled = false;
} // namespace Zest

int main()
{
    long dial = 50;
    uint32_t zeros1 = 0;
    uint32_t zeros2 = 0;
    auto in = file_read(APP_ROOT "/inputs/1.txt");

    // P1
    auto commands = string_split(in, "\r\n");
    for (auto& c : commands)
    {
        auto count = std::stol(&c[1]);
        long pre = dial;
        dial += c[0] == 'L' ? -count : count;
        dial = (dial % 100 + 100) % 100;
        if (dial == 0)
        {
            zeros1++;
        }
    }
    std::cout << "Day1: Part1: " << zeros1 << std::endl;

    // P2
    dial = 50;
    for (auto& c : commands)
    {
        auto count = std::stol(&c[1]);
        count = (c[0] == 'L' ? -count : count);
        while (count != 0)
        {
            dial += (count > 0) ? 1 : -1;
            count += (count > 0) ? -1 : 1;
            dial = (dial % 100 + 100) % 100;
            if (dial == 0)
            {
                zeros2++;
            }
        }
    }
    std::cout << "Day1: Part2: " << zeros2 << std::endl;
}
