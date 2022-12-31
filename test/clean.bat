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

cd %~dp0\..

REM TODO these error checks don't actually work, errorlevel is still 0 even if
REM the rmdir fails for some reason...

if exist test\.build\unit rmdir /s /q test\.build\unit
if %errorlevel% neq 0 exit /b %errorlevel%

if exist .ninja_deps del /AH .ninja_deps
if %errorlevel% neq 0 exit /b %errorlevel%

if exist .ninja_log del /AH .ninja_log
if %errorlevel% neq 0 exit /b %errorlevel%
