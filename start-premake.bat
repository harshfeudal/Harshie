@echo off
setlocal

rem Check if premake5.exe exists in the current directory
if not exist premake5.exe (
    echo Error: premake5.exe not found in the current directory.
    exit /b 1
)

rem Run Premake to generate Visual Studio 2022 project files
premake5 vs2022

endlocal