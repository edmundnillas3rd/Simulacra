@echo off
mkdir bin
mkdir build
pushd build
cl /Zi "..\Simulacra\src\platform\*.c" /link /out:Simulacra.exe
popd