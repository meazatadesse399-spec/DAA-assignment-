@echo off
set CXX="C:\Program Files\CodeBlocks\MinGW\bin\g++.exe"
where g++ >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    set CXX=g++
)

echo ===================================================
echo Compiling Network MST Program (C++17)...
echo ===================================================
%CXX% -std=c++17 -Wall -Wextra -Iinclude src\DSU.cpp src\Kruskal.cpp src\InputHandler.cpp src\main.cpp -o network_mst.exe
if %ERRORLEVEL% EQU 0 (
    echo [SUCCESS] Compilation successful! Created network_mst.exe
) else (
    echo [ERROR] Compilation failed.
)
