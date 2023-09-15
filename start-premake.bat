@echo off
setlocal

set "open_sln=false"

rem Check for command-line arguments: `--open` or `-o` to open Visual Studio directly
for %%i in (%*) do (
    if /I "%%i"=="--open" (
        set "open_sln=true"
    )
)

rem Check if premake5.exe exists in the current directory
if not exist premake5.exe (
    echo Error: premake5.exe not found in the current directory.
    exit /b 1
)

rem Run Premake to generate Visual Studio 2022 project files
premake5 vs2022

rem Check if the .sln file was generated successfully
if exist "Harshie.sln" (
    echo Visual Studio solution file generated successfully.
    
    rem If the "--open:true" argument was provided, open the generated solution file
    if %open_sln%==true (
        start "Visual Studio Solution" "Harshie.sln"
    )
) else (
    echo Error: Visual Studio solution file not generated.
    exit /b 1
)

endlocal
