#include "common.h"

#include "fileutils.h"
#include "stringutils.h"
#include "utils.h"

#include <mutils/logger/logger.h>

#include <set>
#include <numeric>
#include <deque>
#include <algorithm>

#include "ringitr.h"

using namespace std;
using namespace MUtils;

using IntItr = RingIterator<int, std::vector<int>>;

REGISTER_PROBLEM(RAIL)
{
    auto input = string_split(file_read(PRACTICE_ROOT "/advent_of_code/2018/inputs/StationsAndLines.txt"), "\n");

    struct Station
    {
        Station(const std::string& id)
        {
            name = id;
        }
        int distance = std::numeric_limits<int>::max();
        std::string name;
    };
    std::map<string, std::vector<Station*>> mapLineToStations;
    std::map<Station*, std::set<string>> mapStationToLines;
    std::vector<Station*> stations;
    std::string currentLine;
    for (std::string s : input)
    {
        s = string_trim(s);
        if (s.find("Line") != std::string::npos)
        {
            currentLine = s.substr(6);
        }
        else
        {
            auto pStation = new Station(s);
            mapLineToStations[currentLine].push_back(pStation);
            mapStationToLines[pStation].insert(currentLine);
            stations.push_back(pStation);
        }
    }

    std::map<Station*, std::set<Station*>> mapAdjacent;

    // For all stations
    for (auto& spair : mapStationToLines)
    {
        auto& station = spair.first;

        // Walk the lines this station is in
        for (auto& line : mapStationToLines[station])
        {
            auto itrStations = mapLineToStations.find(line);
            auto& vecStations = itrStations->second;
            auto itrFound = std::find(vecStations.begin(), vecStations.end(), station);
            if (itrFound != vecStations.begin())
            {
                mapAdjacent[station].insert(*(itrFound - 1));
            }
            if (itrFound < (vecStations.end() - 1))
            {
                mapAdjacent[station].insert(*(itrFound + 1));
            }
        }
    }

    auto start = stations[0];
    auto end = stations[stations.size()  - 1];

    std::set<Station*> visited;
    visited.insert(start);

    LOG(INFO) << start->name;

    using tVisitor = std::function<void(Station*, int depth)>;
    tVisitor search = [&](Station* station, int depth) 
    {
        station->distance = std::min(station->distance, depth);
        for (auto adj : mapAdjacent[station])
        {
            if (visited.find(adj) == visited.end())
            { 
                visited.insert(adj);
                search(adj, depth + 1);
            }
        }
    };

    int depth = 0;
    search(start, depth);

    using tPathSearch = std::function<void(Station*, std::vector<Station*>&)>;
    tPathSearch pathSearch = [&](Station* station, std::vector<Station*>& visited) 
    {
        int min = std::numeric_limits<int>::max();
        Station* current = nullptr;
        for (auto adj : mapAdjacent[station])
        {
            if (adj == end)
            {
                break;
            }
            if (adj->distance < min)
            {
                min = adj->distance;
                current = adj;
            }
        }

        visited.push_back(current);
        if (current != end)
        {
            pathSearch(current, visited);
        }
    };

    std::vector<Station*> trip;
    pathSearch(end, trip);

    std::reverse(trip.begin(), trip.end());

    for (auto& station : trip)
    {
        LOG(INFO) << station->name;
    }
}
