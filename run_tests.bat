@echo off
set CXX="C:\Program Files\CodeBlocks\MinGW\bin\g++.exe"
where g++ >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    set CXX=g++
)

echo ===================================================
echo Compiling and Running Test Suite (C++17)...
echo ===================================================
%CXX% -std=c++17 -Wall -Wextra -Iinclude src\DSU.cpp src\Kruskal.cpp src\InputHandler.cpp tests\test_suite.cpp -o test_suite.exe
if %ERRORLEVEL% EQU 0 (
    echo [SUCCESS] Test suite compiled. Running tests now...
    echo.
    test_suite.exe
) else (
    echo [ERROR] Test suite compilation failed.
)
