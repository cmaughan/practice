#pragma once

class Fasta
{
public:
    Fasta(const std::string& filePath);

    struct FastaEntry
    {
        std::string name;
        std::string description;
        std::string data;
    };
    typedef std::vector<FastaEntry> FastaEntries_t;

    const FastaEntries_t& GetEntries() const { return _entries; }

private:
    FastaEntries_t _entries;

};