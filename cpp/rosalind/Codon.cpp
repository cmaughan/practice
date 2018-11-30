#include "rosalind.h"
#include "Codon.h"
#include "utils.h"
#include "stringutils.h"
#include <algorithm>

using namespace std;
Codon::Codon()
{
    std::string codons = R"(UUU F      CUU L      AUU I      GUU V
        UUC F      CUC L      AUC I      GUC V
        UUA L      CUA L      AUA I      GUA V
        UUG L      CUG L      AUG M      GUG V
        UCU S      CCU P      ACU T      GCU A
        UCC S      CCC P      ACC T      GCC A
        UCA S      CCA P      ACA T      GCA A
        UCG S      CCG P      ACG T      GCG A
        UAU Y      CAU H      AAU N      GAU D
        UAC Y      CAC H      AAC N      GAC D
        UAA Stop   CAA Q      AAA K      GAA E
        UAG Stop   CAG Q      AAG K      GAG E
        UGU C      CGU R      AGU S      GGU G
        UGC C      CGC R      AGC S      GGC G
        UGA Stop   CGA R      AGA R      GGA G
        UGG W      CGG R      AGG R      GGG G)";

    auto codonEntries = string_split(codons," ");
    _entries = utils_convert_to_pairs(codonEntries);
    utils_erase_if(_entries, [&](const std::pair<std::string, std::string>& pair) {
        if (pair.second == "Stop")
            return true;
        return false;
    });
}

std::string Codon::Map(const std::string& str) const
{
    auto itr = _entries.find(str);
    if (itr == _entries.end())
    {
        return "";
    }
    return itr->second;
}