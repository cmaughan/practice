#include "Common.h"
#include "fileutils.h"

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
        el::Configurations conf(std::string(PRACTICE_ROOT "/logger.conf"));
        el::Loggers::reconfigureAllLoggers(conf);

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

            LOG(INFO) << std::endl << "Problem: " << problemArg.getValue();
            auto pObj = pFactory->create();
            pObj->Run();
            delete pObj;

        }
        else
        {
            for (auto& p : Object::GetFactories())
            {
                LOG(INFO) << std::endl << "Problem: " << p.first;
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

