@echo off
@REM If you have mysys64 installed, it has a shell runner for windows
@REM %* is to add all argument to the shell script if they are passed from windows
C:\msys64\msys2_shell.cmd -defterm -no-start -mingw64 -here .\CYTruck.sh %*