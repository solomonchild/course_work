@ECHO OFF
make
if ERRORLEVEL 0 (
bin\course.exe %1
)
