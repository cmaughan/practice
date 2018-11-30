#include "rosalind.h"

#include "Fasta.h"

inline std::pair<std::string::size_type, std::string::size_type> GetToken(std::string& s, unsigned int offset = 0, const char* t = " \t\n\r\f\v")
{
    std::pair<std::string::size_type, std::string::size_type> ret;
    ret.first = s.find_first_not_of(t, offset);
    if (ret.first == std::string::npos)
    {
        return ret;
    }

    ret.second = s.find_first_of(t, ret.first);
    if (ret.second == std::string::npos)
    {
        ret.second = s.size() - ret.first;
    }
    else
    {
        ret.second = ret.second - ret.first;
    }
    return ret;
}

Fasta::Fasta(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (file.is_open())
    {
        FastaEntry entry;

        enum class ParseState { Name, Data };
        ParseState currentState = ParseState::Name;

        auto pushEntry = [&] ()
        {
            if (currentState != ParseState::Name)
            {
                _entries.push_back(entry);
                entry.data.clear();
                entry.description.clear();
                entry.name.clear();

                //std::cout << "Entry: " << _entries[_entries.size() - 1].name << std::endl;
                //std::cout << "Desc:  " << _entries[_entries.size() - 1].description << std::endl;
                //std::cout << "Data:  " << _entries[_entries.size() - 1].data << std::endl << std::endl;
            }
        };

        std::string str;
        while (std::getline(file, str))
        {
            if (str.empty())
            {
                continue;
            }

            if (str[0] == '>')
            {
                pushEntry();
                auto location = GetToken(str, 1);
                
                currentState = ParseState::Data;
                entry.name = string_trim(str.substr(location.first, location.second));
                
                auto nextPos = location.first + location.second;
                if (nextPos < str.size())
                {
                    entry.description = string_trim(str.substr(nextPos, str.size() - nextPos));
                }
            }
            else
            {
                if (currentState == ParseState::Data)
                {
                    entry.data += string_trim(str);
                }
            }
        }

        pushEntry();
    }
}