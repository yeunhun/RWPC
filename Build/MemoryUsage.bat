@echo off

setlocal Enabledelayedexpansion

IF "%GHS_HOME%"=="" set GHS_HOME=C:\GHS\V800.V2015.1.7\comp_201517
set PATH=%PATH%;%GHS_HOME%

REM Calculate memory usage
set RAM_MAX=262144
set ROM_MAX=1867776
set kSize=1024

set i=0

for /f %%f in ('dir .\debug\*.elf /b') do set filename=%%f
for /f "tokens=2 delims= " %%a IN ('%GHS_HOME%\gsize.exe -ram -rom .\debug\%filename%') do (
	set result[!i!]=%%a
	set /a i=i+1
)

set /a RAM_kSize=result[0]/kSize

set /a RAM_Rate=result[0]*100/RAM_MAX
set /a RAM_Remainder=result[0]-(RAM_Rate*RAM_MAX/100)
set /a RAM_Ratefp=((RAM_Remainder*10000/RAM_MAX+5))/10

set /a ROM_kSize=result[1]/kSize
set /a ROM_Rate=result[1]*100/ROM_MAX
set /a ROM_Remainder=result[1]-(ROM_Rate*ROM_MAX/100)
set /a ROM_Ratefp=((ROM_Remainder*10000)/ROM_MAX+5)/10

echo.
echo ===========================================
echo RAM_Size : %result[0]% bytes  / %RAM_kSize% KB (%RAM_Rate%.%RAM_Ratefp% %%)
echo ROM_Size : %result[1]% bytes  / %ROM_kSize% KB (%ROM_Rate%.%ROM_Ratefp% %%)
echo ===========================================

endlocal

exit /B %ERRORLEVEL%
::pause
