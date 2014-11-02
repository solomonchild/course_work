@ECHO OFF
make
if %ERRORLEVEL% NEQ 0 (
    goto HALT
)
bin\course.exe %1

:HALT
