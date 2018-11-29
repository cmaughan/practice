set CURRENT_DIR=%CD%
mkdir build > nul
cd build
cmake -G "Visual Studio 15 2017 Win64" -DPROJECT_MASSETBUILDER=OFF -DPROJECT_MGEO=OFF ..\
cd "%CURRENT_DIR%"

