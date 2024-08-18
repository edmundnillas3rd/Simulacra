@echo off
mkdir build > NUL 2>&1

pushd build
cl /c /Zi "..\Simulacra\src\platform\*.c" 
lib /OUT:Simulacra.lib "*.obj" user32.lib
cl /Zi /FeSimulacra.exe "..\Sandbox\src\*.c" /I..\Simulacra Simulacra.lib
popd

call build\Simulacra.exe