#pragma once

#include <set>
#include <vector>

// From nucleotide char to 0->4
#define N_TO_INDEX(n) ((n >> 1) & 0x3)

static const char INDEX_TO_N[4]{ 'A', 'C', 'T', 'G' };

template<typename HashT> 
HashT KMer_ToHash(const char* pChar, uint32_t kMerLength)
{
    assert(kMerLength <= ((sizeof(HashT) * 8) / 2));
    HashT val = 0;
    for (uint32_t i = 0; i < kMerLength; i++)
    {
        val |= (N_TO_INDEX(pChar[i]) << (i * 2));
    }
    return val;
}

template<typename HashT>
void KMer_FromHash(std::string& out, HashT hash, uint32_t kMerLength )
{
    out.resize(kMerLength);
    for (uint32_t i = 0; i < kMerLength; i++)
    {
        out[i] = INDEX_TO_N[(hash >> (i * 2)) & 0x3];
    }
}

template<typename HashT> 
std::vector<HashT> KMer_MakeFrequencyTable(uint32_t kMerLength) { return std::vector<HashT>(uint32_t(std::pow(4u, kMerLength))); }

template<typename HashT>
void KMer_ClearFrequencyTable(std::vector<HashT>& table)
{
    memset(&table[0], 0, table.size() * sizeof(HashT));
}

template<typename HashT>
void KMer_PopulateFrequencyTable(std::vector<HashT>& table, std::set<HashT>& clumps, uint32_t frequency, const char* pChar, uint32_t size, uint32_t kMerLength)
{
    for (uint32_t i = 0; i <= size - kMerLength; i++)
    {
        auto hash = KMer_ToHash<HashT>(pChar + i, kMerLength);
        table[hash]++;

        if (table[hash] >= frequency)
        {
            clumps.insert(hash);
        }
        /*std::string out;
        KMer_FromHash(out, hash, kMerLength);
        assert(out == std::string(pChar + i, kMerLength));*/
    }
}

template<typename HashT>
void KMer_UpdateFrequencyTable(std::vector<HashT>& table, std::set<HashT>& clumps, uint32_t frequency, const char* pRemove, const char* pAdd, uint32_t kMerLength)
{
    auto removeHash = KMer_ToHash<HashT>(pRemove, kMerLength);
    auto addHash = KMer_ToHash<HashT>(pAdd, kMerLength);
    assert(table[removeHash] > 0);
    table[removeHash]--;
    if (table[removeHash] < frequency)
    {
        clumps.erase(removeHash);
    }
    table[addHash]++;
    if (table[addHash] >= frequency)
    {
        clumps.insert(addHash);
    }
}
