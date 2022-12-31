@echo off
setlocal enabledelayedexpansion
cd %~dp0

for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -find **\vcvarsall.bat`) do (SET "vcvarsall=%%i")
where cl 1>NUL 2>NUL
if %errorlevel% neq 0 call "%vcvarsall%" amd64
if %errorlevel% neq 0 exit /b %errorlevel%

cl /W4 /WX /I../../include /Fetest_ghost_input.exe *.c
if %errorlevel% neq 0 exit /b %errorlevel%

test_ghost_input
if %errorlevel% neq 0 exit /b %errorlevel%
