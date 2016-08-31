@echo off

set BUILD_TYPE=Debug
if [%1]==[Release] (
    set BUILD_TYPE=Release
)
set BUILD_FOLDER=_build_%BUILD_TYPE%

if not exist %BUILD_FOLDER% (
    mkdir %BUILD_FOLDER%
)

cd %BUILD_FOLDER%
cmake -G "Visual Studio 14 2015 Win64" ../ 
cd ../
