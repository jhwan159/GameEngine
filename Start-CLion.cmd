@echo off
setlocal EnableExtensions DisableDelayedExpansion
rem Start the existing folder with this machine's MSVC environment.
set "ENGINE_CLION_EXE=C:\Users\choja\Applications\CLion\2026.2.3\bin\clion64.exe"
if not exist "%ENGINE_CLION_EXE%" (
  echo ERROR: CLion was not found at "%ENGINE_CLION_EXE%". 1>&2
  echo Installation and configuration are still in progress. 1>&2
  exit /b 1
)
if /i "%~1"=="--check" goto check
call "%~dp0Start-Dev.cmd" --terminal
if errorlevel 1 exit /b %ERRORLEVEL%
start "" "%ENGINE_CLION_EXE%" "%~dp0."
exit /b %ERRORLEVEL%

:check
call "%~dp0Start-Dev.cmd" --check
exit /b %ERRORLEVEL%
