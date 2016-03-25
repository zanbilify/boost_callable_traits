@echo off

set startdir=%cd%

cd C:\mingw*
set mingw_dir=%cd%

cd %startdir%
cd internal
call MinGW.bat %mingw_dir% ..\..\..\
cd %startdir%