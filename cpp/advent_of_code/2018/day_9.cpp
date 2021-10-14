#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"
#include <glm/glm.hpp>

#include "ringitr.h"
#include "utils/Allocator.h"

using namespace std;
using namespace MUtils;

REGISTER_PROBLEM(AOC_2018_Day9)
{
    Timer t("Timer");

    uint64_t playerCount = 441;
    uint64_t maxCount = 71032 * 100;
    
    using ringItrIntPlayers = RingIterator<uint64_t, std::list<uint64_t>>;
    std::list<uint64_t> players(playerCount, 0);
    auto itrPlayer = ringItrIntPlayers(players);

    using ringItrInt = RingIterator<uint64_t, std::list<uint64_t>>;
    std::list<uint64_t> marbles;
    auto itr = ringItrInt(marbles);

    int currentMarble = 0;
    do
    {
        if (currentMarble != 0 &&
            (currentMarble % 23) == 0)
        {
            *itrPlayer += currentMarble;
            for (int i = 0; i <= 7; i++)
            {
                itr--;
            }
            *itrPlayer += *itr;
            itr = itr.erase();
            itr++;
        }
        else
        {
            itr = itr.insertAfter(currentMarble);
            itr++;
        }
        
        /*
        std::ostringstream str;
        for (auto& mar : marbles)
        {
            str << mar << " ";
        }
        std::cout << str.str() << std::endl;
        */

        currentMarble++;
        itrPlayer++;

    } while (currentMarble <= maxCount);
 
    auto itrElf = std::max_element(players.begin(), players.end());

    LOG(INFO) << "Part 1: " << *itrElf;
    LOG(INFO) << "Part 2: " << 2;
}

