@echo off

set startdir=%cd%

cd "C:\Users\barre\Documents\GitHub\callable_traits"
FOR /d %%a in (.\build*) DO RD /s /q %%a

cd C:\mingw*
set mingw_dir=%cd%

cd %startdir%
cd internal
call MinGW-no-experimental.bat %mingw_dir% ..\..\..\
cd %startdir%