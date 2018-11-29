#include <windows.h>
#include <shlobj.h>

#include "fileutils.h"
#include <queue>
#include <set>
#include <filesystem>
#include <fstream>

std::string file_read(const fs::path& fileName)
{
    std::ifstream in(fileName, std::ios::in | std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(size_t(in.tellg()));
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    return std::string();
}

bool file_write(const fs::path& fileName, const void* pData, size_t size)
{
    FILE* pFile = nullptr;
    fopen_s(&pFile, fileName.string().c_str(), "wb");
    if (!pFile)
    {
        return false;
    }
    fwrite(pData, sizeof(uint8_t), size, pFile);
    fclose(pFile);
    return true;
}