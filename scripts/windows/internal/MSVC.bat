::should've used PowerShell - oh well

@echo off

set project_root=%3
set project_name=%4

::process 1st argument
if "%~1"=="x64" (
  set cmake_cmd=cmake .. -G"Visual Studio 14 2015 Win64" -DCALLABLE_TRAITS_BUILD_EXPERIMENTAL=ON
) else (
  if "%~1"=="Win32" (
    set cmake_cmd=cmake .. -G"Visual Studio 14 2015" -DCALLABLE_TRAITS_BUILD_EXPERIMENTAL=ON
  )
)
if not defined cmake_cmd (
  echo BUILD SCRIPT: ERROR: Invalid parameter: %1 - expected 'Win32' or 'x64'
  call :exit_script
)

::process 2nd argument
if "%~2"=="Release" (
  set config_success="0"
  
) else (
  if "%~2"=="Debug" (
    set config_success="0"
  )
)
if not defined config_success (
  echo BUILD SCRIPT: ERROR: Invalid parameter: %2 - expected 'Release' or 'Debug'
  call :exit_script
)

::process 3rd argument
if "%~2"=="Release" (
  set config_success="0"
  
) else (
  if "%~2"=="Debug" (
    set config_success="0"
  )
)
if not defined config_success (
  echo BUILD SCRIPT: ERROR: Invalid parameter: %2 - expected 'Release' or 'Debug'
  call :exit_script
)

set msbuild_environment=/p:Configuration=%2 /p:Platform=%1
echo BUILD SCRIPT: Preparing %1 %2 build...

::find MSBuild.exe
if exist "%ProgramFiles%\MSBuild\14.0\Bin\MSBuild.exe" (
  echo BUILD SCRIPT: MSBuild.exe found...
  set msbuild_cmd="%ProgramFiles%\MSBuild\14.0\Bin\MSBuild.exe"
) else (
  if exist "%ProgramFiles(x86)%\MSBuild\14.0\Bin\MSBuild.exe" (
    echo BUILD SCRIPT: MSBuild.exe found...
    set msbuild_cmd="%ProgramFiles(x86)%\MSBuild\14.0\Bin\MSBuild.exe"
  )
)
if not defined msbuild_cmd (
  echo BUILD SCRIPT: ERROR: MSBuild.exe not found... is Visual Studio 2015 installed?
  call :exit_script
)

cd %project_root%
set build_dir= "build_MSVC_%1_%2"

echo BUILD SCRIPT: Building at %build_dir%...

if exist %build_dir% (
  cd %build_dir%
  if exist "%project_name%.sln" (
    echo BUILD SCRIPT: %project_name%.sln found - cleaning...
    echo . | %msbuild_cmd% %project_name%.sln /t:clean %msbuild_environment% /v:m /m /nologo
	cd ..\
  ) else (
    echo BUILD SCRIPT: %project_name%.sln not found - deleting build directory...
    cd ..
    rmdir /q /s %build_dir%
  )
)

if exist %build_dir% (
  cd %build_dir%
) else (
  echo BUILD SCRIPT: Creating build directory...
  mkdir %build_dir%
  cd %build_dir%
  echo BUILD SCRIPT: Running cmake...
  echo . | %cmake_cmd%
  echo BUILD SCRIPT: %project_name%.sln...
  echo . | %msbuild_cmd% %project_name%.sln %msbuild_environment% /v:m /m /nologo
)

echo BUILD SCRIPT: CHECK.vcxproj...
echo . | %msbuild_cmd% CHECK.vcxproj %msbuild_environment%

::echo BUILD SCRIPT: doc/doc.vcxproj...
::echo . | %msbuild_cmd% doc\doc.vcxproj %msbuild_environment%

:exit_script
::pause if this script was started by double clicked from Windows
::Explorer instead of starting from a pre-existing cmd.exe window
for %%x in (%cmdcmdline%) do if /i "%%~x"=="/c" set CLICKED=1
if defined CLICKED pause

cd ..\scripts

