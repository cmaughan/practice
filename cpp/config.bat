set CURRENT_DIR=%CD%
@echo off
mkdir build > nul
cd build
if "%1" == "docs" goto docs
cmake -G "Visual Studio 16 2019" -A x64 ..\
goto end
:docs
cmake -G "Visual Studio 16 2019" -A x64 -DBUILD_DOCS=1 ..\
goto end
:end
cd "%CURRENT_DIR%"

