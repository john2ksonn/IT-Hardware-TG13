@echo off

REM Maybe change this path to match your installation
SET batchisp_path="C:\Program Files (x86)\Atmel\Flip 3.4.7\bin\batchisp.exe"
SET uv4_path="C:\Keil_v5\UV4\UV4.exe"
REM name of the uvproj file without ending
SET project_name=CHANGE_THIS_TO_MATCH_YOUR_PROJECT

REM Change dir to the projects dir
CD %1

REM Goto the specified targed
GOTO %2

REM Burn the hexfile and exit
:burn
    %batchisp_path% -device AT89C5131 -hardware usb -operation erase f blankcheck loadbuffer "Objects\%project_name%.hex" program verify
    exit %ERRORLEVEL%

REM Compile and goto the next target or exit
:compile
    %uv4_path% -r %project_name%.uvproj -t "Target 1" -o tmp.log -jO
    set el=%ERRORLEVEL%
    TYPE tmp.log
    DEL tmp.log
    if %el% NEQ 2 (
        GOTO %3
    )
    exit %el%

REM simply exit with an errorlevel
:exit
    exit %el%
