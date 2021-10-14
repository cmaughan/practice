#pragma once

#include "common.h"
#include <string>
#include <fstream>

#include "Fasta.h"
#include "Codon.h"

#include "fileutils.h"
#include "stringutils.h"

#include "mutils/logger/logger.h"

extern std::string g_CurrentProblem;

inline std::string rosalind_input()
{
    return PRACTICE_ROOT "/rosalind/data/rosalind_" + g_CurrentProblem + ".txt";
}

inline std::string rosalind_output()
{
    return PRACTICE_ROOT "/rosalind/data/rosalind_" + g_CurrentProblem + "_out.txt";
}

inline std::string ReadInput()
{
    using namespace MUtils;
    std::ifstream t(rosalind_input());
    if (!t.is_open())
    {
        LOG(ERROR) << "File not found: " << rosalind_input();
        return std::string();
    }
    return std::string((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
}

inline std::shared_ptr<Fasta> ReadInputFasta()
{
    return std::make_shared<Fasta>(rosalind_input());
}

inline void WriteOutput(const std::string& out)
{
    using namespace MUtils;
    std::ofstream t(rosalind_output());
    if (!t.is_open())
    {
        LOG(ERROR) << "Couldn't write: " << rosalind_output();
        return;
    }

    t << out;

    LOG(INFO) << out;
}

