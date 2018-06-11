@echo off
:loop
data.exe
E.exe
test.exe
fc E.txt _E.txt
if not errorlevel 1 goto loop
pause
:end