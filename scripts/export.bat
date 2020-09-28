echo off
cd ..
mkdir export
cd export
"C:\Program Files\7-Zip\7z.exe" a -tzip archive.zip -r ../bin/Release-32 ../bin/Release-64 ../bin/LauncherPy/dist/main.exe

pause