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

REM Builds and runs the unit test suite under the Visual Studio C/C++ compiler
REM on Windows.
REM
REM You will need Python on your PATH and Visual Studio installed with whatever
REM build tools you intend to use.
REM
REM You can run this in a normal command prompt or in a Visual Studio Build
REM Tools command prompt. It will find the build tools automatically if needed
REM but it will start up a lot faster if they are already available.
REM
REM Pass -arch <arch> to choose architecture, x86 or amd64
REM Pass -vcvars_ver <ver> to choose version, e.g.:
REM     - 14.0  for 2015
REM     - 14.16 for 2017
REM     - 14.29 for 2019
REM     - 14.31 (or 14.30) for 2022
REM The above arguments will be ignored if build tools already exist on your
REM PATH (i.e. if build tools are already loaded.)
REM
REM Pass additional arguments to be forwarded to ninja
REM     (e.g. all, more, run-default-release)

setlocal enabledelayedexpansion

cd %~dp0\..

REM Find build tools
for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -find **\vcvarsall.bat`) do (SET "vcvarsall=%%i")
echo Found tools %vcvarsall%

REM Parse arguments
SET vcvars_ver=
SET arch=amd64
SET rest=
:parse_args
IF NOT "%1"=="" (
    IF "%1"=="-vcvars_ver" (
        SET vcvars_ver=%2
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
where cl 1>NUL 2>NUL
if %errorlevel% neq 0 call "%vcvarsall%" %arch% -vcvars_ver=%vcvars_ver%
if %errorlevel% neq 0 exit /b %errorlevel%

REM Configure unit tests
python test\unit\configure.py
if %errorlevel% neq 0 exit /b %errorlevel%

REM Run unit tests
ninja -f test\.build\unit\build.ninja %rest%
if %errorlevel% neq 0 exit /b %errorlevel%
