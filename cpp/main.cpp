#include "Common.h"

#include <tclap/CmdLine.h>
#include <map>

using namespace std;

TCLAP::ValueArg<std::string> problemArg("p", "problem", "Problem to run", false, "", "");
TCLAP::ValueArg<std::string> dirArg("d", "data", "Data path", false, "data", "string");

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv)
{
    try
    {
        // Parse the command line
        TCLAP::CmdLine cmd("AOC", ' ', "1.0");
        cmd.setExceptionHandling(false);

        cmd.add(problemArg);
        cmd.add(dirArg);

        // Parse the argv array.
        cmd.parse(argc, argv);

        if (problemArg.isSet())
        {
            ObjectFactory* pFactory = nullptr;
            for (auto& p : Object::GetFactories())
            {
                if (p.first == problemArg.getValue())
                {
                    pFactory = p.second;
                }
            }

            if (pFactory == nullptr)
            {
                std::cerr << "Error: " << problemArg.getValue() << " problem not found!" << std::endl;
                return 1;
            }

            auto pObj = pFactory->create();
            pObj->Run();
            delete pObj;

        }
        else
        {
            for (auto& p : Object::GetFactories())
            {
                auto pObj = p.second->create();
                pObj->Run();
                delete pObj;
            }
        }
    }
    catch (TCLAP::ArgException& e)
    {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    }

    system("pause");

    return 0;
}

/*
std::string GetInputPath()
{
    return dirArg.getValue() + "/rosalind_" + problemArg.getValue() + ".txt";
}

std::string GetOutputPath()
{
    return dirArg.getValue() + "/rosalind_" + problemArg.getValue() + "_out.txt";
}

std::string ReadInput()
{
    std::ifstream t(GetInputPath());
    if (!t.is_open())
    {
        std::cerr << "File not found: " << GetInputPath() << std::endl;
        return std::string();
    }
    return std::string((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
}

void WriteOutput(const std::string& out)
{
    std::ofstream t(GetOutputPath());
    if (!t.is_open())
    {
        std::cerr << "Couldn't write: " << GetOutputPath() << std::endl;
        return;
    }

    t << out;

    std::cout << out;
}
*/

/*
// adventofcode.cpp : Defines the entry point for the console application.
//

#include <algorithm>
#include <numeric>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <chrono>
#include <cassert>
#include <map>
#include <set>
#define GLM_ENABLE_EXPERIMENTAL
#include <unordered_map>
#include <unordered_set>
#include <streambuf>

#include "utils.h"
#include "glm/glm.hpp"
#include "glm/gtx/hash.hpp"
#include "ringitr.h"

using namespace std;

void ShowResult(const std::string& strName, int val)
{
    std::cout << strName << ": " << val << std::endl;
}



int main()
{
    using ringItr = RingIterator<char, string>;
    using ringItrVec = RingIterator<string, std::vector<string>>;
    using ringItrInt = RingIterator<int, std::vector<int>>;

    // Part 1:1
    // Find matching pairs, wrap at the end
    string str1("21752342814933766938172121674976879111362417653261522357855816893656462449168377359285244818489723869987861247912289729579296691684761143544956991583942215236568961875851755854977946147178746464675227699149925227227137557479769948569788884399379821111382536722699575759474473273939756348992714667963596189765734743169489599125771443348193383566159843593541134749392569865481578359825844394454173219857919349341442148282229689541561169341622222354651397342928678496478671339383923769856425795211323673389723181967933933832711545885653952861879231537976292517866354812943192728263269524735698423336673735158993853556148833861327959262254756647827739145283577793481526768156921138428318939361859721778556264519643435871835744859243167227889562738712953651128317624673985213525897522378259178625416722152155728615936587369515254936828668564857283226439881266871945998796488472249182538883354186573925183152663862683995449671663285775397453876262722567452435914777363522817594741946638986571793655889466419895996924122915777224499481496837343194149123735355268151941712871245863553836953349887831949788869852929147849489265325843934669999391846286319268686789372513976522282587526866148166337215961493536262851512218794139272361292811529888161198799297966893366553115353639298256788819385272471187213579185523521341651117947676785341146235441411441813242514813227821843819424619974979886871646621918865274574538951761567855845681272364646138584716333599843835167373525248547542442942583122624534494442516259616973235858469131159773167334953658673271599748942956981954699444528689628848694446818825465485122869742839711471129862632128635779658365756362863627135983617613332849756371986376967117549251566281992964573929655589313871976556784849231916513831538254812347116253949818633527185174221565279775766742262687713114114344843534958833372634182176866315441583887177759222598853735114191874277711434653854816841589229914164681364497429324463193669337827467661773833517841763711156376147664749175267212562321567728575765844893232718971471289841171642868948852136818661741238178676857381583155547755219837116125995361896562498721571413742");
    ShowResult("P1,1", inner_product(str1.begin(),       // Start of string
        str1.end(),                           // End of string
        ringItr(str1, 1),                     // Start + 1, with wrap
        0,                                    // Start sum
        [](int a, int b) { return a + b; },   // Accumulate function
        [](const char& ch1, const char& ch2) { return ch1 == ch2 ? (ch1 - '0') : 0;  }));  // Compare function

    // Part 1:2
    // Find matching half size away, with wrap
    ShowResult("P1,2", inner_product(str1.begin(),
        str1.end(),
        ringItr(str1, (str1.size() / 2)),
        0,
        [](int a, int b) { return a + b; },
        [](const char& ch1, const char& ch2) { return ch1 == ch2 ? (ch1 - '0') : 0;  }));

    // Part 2:1
    string str2 = R"(
    116	1259	1045	679	1334	157	277	1217	218	641	1089	136	247	1195	239	834
    269	1751	732	3016	260	6440	5773	4677	306	230	6928	7182	231	2942	2738	3617
    644	128	89	361	530	97	35	604	535	297	599	121	567	106	114	480
    105	408	120	363	430	102	137	283	123	258	19	101	181	477	463	279
    873	116	840	105	285	238	540	22	117	125	699	953	920	106	113	259
    3695	161	186	2188	3611	2802	157	2154	3394	145	2725	1327	3741	2493	3607	4041
    140	1401	110	119	112	1586	125	937	1469	1015	879	1798	122	1151	100	926
    2401	191	219	607	267	2362	932	2283	889	2567	2171	2409	1078	2247	2441	245
    928	1142	957	1155	922	1039	452	285	467	305	506	221	281	59	667	232
    3882	1698	170	5796	2557	173	1228	4630	174	3508	5629	4395	180	5100	2814	2247
    396	311	223	227	340	313	355	469	229	162	107	76	363	132	453	161
    627	1331	1143	1572	966	388	198	2068	201	239	176	1805	1506	1890	1980	1887
    3390	5336	1730	4072	5342	216	3823	85	5408	5774	247	5308	232	256	5214	787
    176	1694	1787	1586	3798	4243	157	4224	3603	2121	3733	851	2493	4136	148	153
    2432	4030	3397	4032	3952	2727	157	3284	3450	3229	4169	3471	4255	155	127	186
    919	615	335	816	138	97	881	790	855	89	451	789	423	108	95	116
    )";

    // P2, 1: Find max/min for each array line, sum the min/max range into a total for all lines
    auto arrayLines = GetIntegerGrid(str2);
    ShowResult("P2,1", accumulate(arrayLines.begin(), arrayLines.end(), 0, [](int range, const vector<int>& vals)
    {
        // Gather min max for row
        auto minMax = minmax_element(vals.begin(), vals.end());
        return range + int(*minMax.second - *minMax.first);
    }));

    // Find even divisors
    // Find the pair of numbers that divides and sum it
    ShowResult("P2,2", accumulate(arrayLines.begin(), arrayLines.end(), 0, [](int total, vector<int>& vals)
    {
        return total + accumulate_pairs(vals, 0, [](auto ret, auto v1, auto v2)
        {
            return ret + ((v1 % v2 == 0) ? (v1 / v2) : 0);
        });
    }));

    // P3, 1: Spiral Memory
    auto coord = UlamIndexToCoords(368078);
    ShowResult("P3,1", std::abs(coord.x) + std::abs(coord.y));

    // P3, 2: Walk and accumulate surrounds
    std::unordered_map<glm::ivec2, int> spiralVals{ { glm::ivec2(0, 0), 1 } };
    std::vector<glm::ivec2> surrounds{ {1, 0}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {-1, 1}, {0, 1}, {1, 1} };
    int currentIndex = 1;
    do
    {
        coord = UlamIndexToCoords(++currentIndex);
        for (auto& offset : surrounds)
        {
            auto itr = spiralVals.find(coord + offset);
            spiralVals[coord] += (itr != spiralVals.end() ? itr->second : 0);
        }
    } while (spiralVals[coord] < 368078);
    ShowResult("P3,2", spiralVals[coord]);

    std::ifstream t("p4input.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    auto p4lines = GetStringGrid(buffer.str());

    auto FindDuplicates = [p4lines](bool anagrams = false)
    {
        int badCount = 0;
        for (auto& l : p4lines)
        {
            std::set<std::string> entries;
            for (auto w : l)
            {
                if (anagrams)
                    std::sort(w.begin(), w.end());

                if (entries.find(w) != entries.end())
                {
                    badCount++;
                    break;
                }
                entries.insert(w);
            }
        }
        return int(p4lines.size()) - badCount;
    };
    ShowResult("P4,1", FindDuplicates());
    ShowResult("P4,2", FindDuplicates(true));

    std::ifstream p5file("p5input.txt");
    std::vector<int> jumps{ std::istream_iterator<int>{p5file}, {} };
    int ic = 0;
    int steps = 0;
    while (ic >= 0 && ic < jumps.size())
    {
        ic = ic + jumps[ic]++;
        steps++;
    }
    ShowResult("P5,1", steps);

    /*
    p5file.clear();
    p5file.seekg(0, ios::beg);
    jumps = std::vector<int>{ std::istream_iterator<int>{p5file}, {} };
    ic = 0;
    steps = 0;
    while (ic >= 0 && ic < jumps.size())
    {
        ic = ic + (jumps[ic] >= 3 ? jumps[ic]-- : jumps[ic]++);
        steps++;
    }
    ShowResult("P5,2", steps);
    */

    /*
    std::string input6 = "10	3	15	10	5	15	5	15	9	2	5	8	5	2	3	6";
    auto banks = std::vector<int>{ std::istream_iterator<int>{std::istringstream(input6)}, {} };
    auto FindLoop = [&banks](bool loopSize = false)
    {
        std::set<std::vector<int>> matches;
        for (;;)
        {
            ringItrInt itr(banks, std::max_element(banks.begin(), banks.end()));
            auto count = size_t(*itr);
            *itr = 0;
            std::for_each_n(itr + 1, count, [](int& val) { val++; });
            if (matches.find(banks) != matches.end())
            {
                if (!loopSize)
                {
                    return int(matches.size());
                }
                loopSize = false;
                matches.clear();
            }
            matches.insert(banks);
        }
    };
    ShowResult("P6,1", FindLoop(false) + 1);

    banks = std::vector<int>{ std::istream_iterator<int>{std::istringstream(input6)}, {} };
    ShowResult("P6,1", FindLoop(true));

    // P7:1
    auto p7input = FileUtils::ReadFile("p7input.txt");
    std::vector<std::string> lines = StringUtils::SplitLines(p7input);

    // A tower disc
    struct disc
    {
        std::string name;
        int weight = 0;
        int childWeights = 0;
        disc* pParent = nullptr;
        std::vector<std::string> childNames;
        std::vector<disc*> children;

        int UpdateWeights()
        {
            childWeights += weight;
            for (auto& ch : children)
            {
                childWeights += ch->UpdateWeights();
            }
            return childWeights;
        }

        disc* FindUnbalanced()
        {
            disc* pRet;
            for (auto& child : children)
            {
                if (!child->Balanced(&pRet))
                {
                    return pRet->FindUnbalanced();
                }
            }
            return this;
        }

        bool Balanced(disc** ppDisc)
        {
            struct mapVal { int v = 0; disc* pDisc = nullptr; void inc(disc* p) { v++; pDisc = p; } };
            std::map<int, mapVal > mapCounts;
            std::for_each(children.begin(), children.end(), [&mapCounts](disc* p) {mapCounts[p->childWeights].inc(p); });
            auto itr = std::find_if(mapCounts.begin(), mapCounts.end(), [&mapCounts](const std::pair<int, mapVal>& entry) { return entry.second.v == 1; });
            if (itr == mapCounts.end())
                return true;
            *ppDisc = itr->second.pDisc;
            return false;
        }
    };
    std::map<std::string, std::shared_ptr<disc>> discs;

    // Pass 1, read the discs
    for (auto& line : lines)
    {
        auto towerEntry = StringUtils::Split(line, " \t,");
        if (towerEntry.empty())
            continue;
        auto d = std::make_shared<disc>();
        d->name = towerEntry[0];
        d->weight = stoi(StringUtils::Trim(towerEntry[1], "()"));

        for (int index = 3; index < towerEntry.size(); index++)
        {
            d->childNames.push_back(towerEntry[index]);
        }
        discs[d->name] = d;
    }

    // Pass 2, build the hierarhcy
    for (auto& d : discs)
    {
        auto& pDisc = d.second;
        for (auto& childName : pDisc->childNames)
        {
            auto itrFound = discs.find(childName);
            if (itrFound != discs.end())
            {
                pDisc->children.push_back(itrFound->second.get());
                itrFound->second->pParent = pDisc.get();
            }
        }
    }

    // Get the root
    auto pRoot = std::find_if(discs.begin(), discs.end(), [](const std::pair<std::string, std::shared_ptr<disc>>& p) { return p.second->pParent == nullptr; })->second;
    ShowResult("P7,1: " + pRoot->name, 0);

    // Build the weights, find the unbalanced disc
    pRoot->UpdateWeights();
    auto pRet = pRoot->FindUnbalanced();
    auto itrSibling = std::find_if(pRet->pParent->children.begin(), pRet->pParent->children.end(), [pRet](disc* pChild) { return pChild != pRet; });

    // Balance result is the discs weight difference from the sibling
    ShowResult("P7,2: ", pRet->weight - (pRet->childWeights - (*itrSibling)->childWeights));

    std::ifstream p8in("p8input.txt");
    std::stringstream p8buffer;
    p8buffer << p8in.rdbuf();
    auto p8grid = GetStringGrid(p8buffer.str());
    enum inputEntry { Reg1, Op, Val1, If, Reg2, Cmp, Val2};
    struct regVal { int v = 0; void inc(int val) { v+= val; } };
    enum class OpType { LESS, GREATER, LEQUAL, GEQUAL, NOTEQUAL, EQUAL };
    std::map<string, regVal> registers;
    std::map<string, OpType> toOp{ { "<", OpType::LESS }, { ">", OpType::GREATER }, {"<=", OpType::LEQUAL}, {">=", OpType::GEQUAL}, {"!=", OpType::NOTEQUAL}, { "==", OpType::EQUAL} };
    int maxVal = std::numeric_limits<int>::min();
    for (auto& line : p8grid)
    {
        bool should = false;
        int val2 = stoi(line[Val2]);
        switch (toOp[line[Cmp]])
        {
        case OpType::LESS:
            should = registers[line[Reg2]].v < val2;
            break;
        case OpType::GREATER:
            should = registers[line[Reg2]].v > val2;
            break;
        case OpType::LEQUAL:
            should = registers[line[Reg2]].v <= val2;
            break;
        case OpType::GEQUAL:
            should = registers[line[Reg2]].v >= val2;
            break;
        case OpType::NOTEQUAL:
            should = registers[line[Reg2]].v != val2;
            break;
        case OpType::EQUAL:
            should = registers[line[Reg2]].v == val2;
            break;
        }
        if (should)
        {
            int val1 = stoi(line[Val1]);
            if (line[Op] == "dec")
                val1 = -val1;
            registers[line[Reg1]].inc(val1);
            maxVal = std::max(maxVal, registers[line[Reg1]].v);
        }
    }
    ShowResult("P8,1: ", std::max_element(registers.begin(), registers.end(), [](const std::pair<std::string, regVal>& r1,
        const std::pair<std::string, regVal>& r2)
    {
        return r1.second.v < r2.second.v;
    })->second.v);

    ShowResult("P8,2: ", maxVal);

    system("pause");

    return 0;
}
*/