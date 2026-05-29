@echo off
pushd %0\..\..
setlocal
set PYTHON_HOME=D:\ts_mirr\python\Portable_Python_2.7.6.1\App
set SCONS_HOME=D:\ts_mirr\scons\scons-local-2.3.4
set PATH=%PATH%;%PYTHON_HOME%;%SCONS_HOME%
set gentoolfw_version=1.1.5

rem ==== 여기부터
IF /i "%1"=="" goto gitLog

set param=%1%
echo With Parameter %param%
goto check_param

:check_param
set result=%param%
IF /i "%result%"=="Hook" goto gitLog
IF /i "%result%"=="Build" goto run_build
IF /i "%result%"=="BuildFBL" goto run_build
IF /i "%result%"=="Compile" goto run_build
IF /i "%result%"=="CompileFBL" goto run_build
IF /i "%result%"=="Debug" goto run_build
IF /i "%result%"=="DebugFBL" goto run_build
IF /i "%result%"=="GenerateAll" goto run_build
IF /i "%result%"=="Rebuild" goto run_build

echo Invalid Parameter. Defaullt "Build"
set result=Build
goto run_build

:gitLog
git log -1 --pretty=format:%%B > last.log
set /p param=< last.log
echo gitLog %param%
goto check_param

:run_build
echo run build with param: %result%
%PYTHON_HOME%\python Build\site_scons\build.pyc %result%
rem 여기까지 추가 =====
::%PYTHON_HOME%\python Build\site_scons\build.pyc %*

IF %ERRORLEVEL%==0 call Build\MemoryUsage.bat

endlocal
popd
exit /B %ERRORLEVEL%
::pause
