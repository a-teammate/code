@ECHO OFF
Setlocal EnableDelayedExpansion

set INEXOR_ARCH=win32

IF /I "%PROCESSOR_ARCHITECTURE%" == "amd64" (
    set INEXOR_ARCH=win64
)
IF /I "%PROCESSOR_ARCHITEW6432%" == "amd64" (
    set INEXOR_ARCH=win64
)

:: Clear variable
set "DATA_DIRS="
:: Find all data repos in media
for /f "delims=" %%a in ('dir "./media" /on /ad /b') do @set "DATA_DIRS=!DATA_DIRS! -kmedia/%%a/"

:: start /B inexor_node_windows.bat
start bin\windows\%INEXOR_ARCH%\inexor.exe "-q$HOME\My Games\Inexor" %DATA_DIRS% -glog.txt %*
