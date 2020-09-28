echo off
cd ..
mkdir bin
cd bin
mkdir LauncherPy
cd LauncherPy
pyinstaller --onefile ../../LauncherPy/src/main.py
pause