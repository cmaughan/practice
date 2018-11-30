#pragma once
#pragma once

class Codon
{
public:
    Codon();

    typedef std::map<std::string, std::string> CodonMap_t;

    std::string Map(const std::string& str) const;

private:
    CodonMap_t _entries;

};