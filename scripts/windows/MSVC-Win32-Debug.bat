@echo off

set startdir=%cd%
cd internal
call MSVC.bat Win32 Debug ..\..\..\ callable_traits
cd %startdir%
