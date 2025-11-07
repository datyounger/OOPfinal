@echo off
echo Compiling Research Management System...
g++ -std=c++11 -Wall -Wextra -o research_manager main.cpp
if %errorlevel% == 0 (
    echo COMPILE SUCCESS!
    echo.
    echo Running program...
    echo.
    research_manager.exe
) else (
    echo COMPILE FAILED!
    echo Check your source files.
)
pause