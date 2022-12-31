@echo off

REM MIT No Attribution
REM
REM Copyright (c) 2022 Fraser Heavy Software
REM
REM Permission is hereby granted, free of charge, to any person obtaining a copy
REM of this software and associated documentation files (the "Software"), to
REM deal in the Software without restriction, including without limitation the
REM rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
REM sell copies of the Software, and to permit persons to whom the Software is
REM furnished to do so.
REM
REM THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
REM IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
REM FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
REM AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
REM LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
REM FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
REM IN THE SOFTWARE.

REM Builds and runs the unit test suite under the Visual Studio 2013 C/C++
REM compiler on Windows.
REM
REM This is like unit.bat but hacked up to use VS2013 because I'm not good
REM enough at batch scripting to make it do both.

setlocal enabledelayedexpansion

cd %~dp0\..

REM Find legacy VS2013 build tools
for /f "usebackq tokens=*" %%i in (`^""%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -legacy -version "[12,13)" -property installationPath^"`) do (SET "vcvarsall2013=%%i\VC\vcvarsall.bat")
echo Found legacy tools %vcvarsall2013%

REM Parse arguments
SET arch=x86
SET rest=
:parse_args
IF NOT "%1"=="" (
    IF "%1"=="-vcvars_ver" (
        REM ignored, don't pass it to ninja
        SHIFT
    ) ELSE IF "%1"=="-arch" (
        SET arch=%2
        SHIFT
    ) ELSE (
        SET rest=%rest% %1
    )
    SHIFT
    GOTO :parse_args
)

REM Collect remaining arguments
:collect_rest
IF NOT "%1"=="" (
    SET rest=%rest% %1
    SHIFT
    GOTO :collect_rest
)

REM Enable build tools if needed
REM (Load the modern tools first to get ninja on the path)
where cl 1>NUL 2>NUL
echo Loading VS2013 legacy tools
if %errorlevel% neq 0 call "%vcvarsall2013%" %arch%
if %errorlevel% neq 0 exit /b %errorlevel%
echo Legacy tools loaded

REM Configure unit tests
python test\unit\configure.py
if %errorlevel% neq 0 exit /b %errorlevel%

REM Run unit tests
REM Note that legacy build tools don't include ninja. You'll need to put it on
REM your PATH yourself, or just copy it to the VC/bin folder.
ninja -f test\.build\unit\build.ninja %rest%
if %errorlevel% neq 0 exit /b %errorlevel%
