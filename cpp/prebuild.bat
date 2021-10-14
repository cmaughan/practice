@echo off

cd mutils
call prebuild.bat
cd ..

cd vcpkg
vcpkg install implot --triplet x64-windows-static-md --recurse
cd %~dp0
