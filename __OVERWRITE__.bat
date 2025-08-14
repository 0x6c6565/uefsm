@echo off

echo Updating repository from %1

set pluginFileName=%~1%\UEFSM.uplugin

echo(
echo Checking for "%pluginFileName%"
echo(

if exist "%pluginFileName%" (
echo copying "%pluginFileName%" to "%~dp0%"
copy "%pluginFileName%" "%~dp0%"
) else (
echo "%pluginFileName%" not found!
pause
exit /b 1
)
echo(

set sourceFolderName=%~1%\Source\
if exist "%sourceFolderName%" (
echo copying "%sourceFolderName%" to "%~dp0%"
xcopy "%sourceFolderName%" "%~dp0%\Source\" /E /Y /H /I
) else (
echo Could not find "%sourceFolderName%" in directory!
)
echo(

set resourcesFolderName=%~1%\Resources\
if exist "%resourcesFolderName%" (
echo copying "%resourcesFolderName%" to "%~dp0%"
xcopy "%resourcesFolderName%" "%~dp0%\Resources\" /E /Y /H /I
) else (
echo Could not file "%resourcesFolderName%" in directory!
)
echo(

echo All files copied.

pause