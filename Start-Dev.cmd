@echo off
rem Configure only this terminal; engine code stays under the human's control.
set "ENGINE_VS_ROOT="
set "ENGINE_VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%ENGINE_VSWHERE%" goto missing_vs
for /f "usebackq tokens=*" %%I in (`"%ENGINE_VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "ENGINE_VS_ROOT=%%I"
if not defined ENGINE_VS_ROOT goto missing_vs
set "VSCMD_START_DIR=%~dp0"
call "%ENGINE_VS_ROOT%\Common7\Tools\VsDevCmd.bat" -no_logo -arch=x64 -host_arch=x64
if errorlevel 1 exit /b 1
set "PATH=%LOCALAPPDATA%\Microsoft\WinGet\Links;%PATH%"
cd /d "%~dp0"
if /i "%~1"=="--check" goto check
if /i "%~1"=="--verify" goto verify
if /i "%~1"=="--terminal" exit /b 0
echo PersonalGameEngine: MSVC x64 developer terminal is ready.
echo Type exit to close this terminal.
"%ComSpec%" /d /k
exit /b %ERRORLEVEL%

:check
for %%T in (cl.exe cmake.exe ninja.exe ctest.exe git.exe node.exe) do (
  where %%T >nul 2>&1
  if errorlevel 1 (
    echo ERROR: %%T was not found.
    exit /b 1
  )
)
cmake --version
if errorlevel 1 exit /b 1
ninja --version
if errorlevel 1 exit /b 1
git --version
if errorlevel 1 exit /b 1
echo Tool paths and versions checked.
exit /b 0

:verify
node "%~dp0tools\verify-environment.mjs"
exit /b %ERRORLEVEL%

:missing_vs
echo ERROR: Visual Studio x64 C++ tools were not found.
exit /b 1
