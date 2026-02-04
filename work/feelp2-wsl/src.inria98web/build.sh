#!/bin/sh
mkdir -p ~/bin
mkdir -p ~/lib

cd exec
make
cp ./feel ~/bin
cd ..
cp bamg/bamg ~/bin
./clean.bat
cd test
make 
cp parse ~/bin/feel.parse
cd ../
cd mesh_bamg_util/BAMG_BTOF_COMMAND
make
cp ./feel.bamg.exe ~/bin
cd ../..
cd feelG
make
cp libfeelG.a ~/lib
cd ALPNUM
gfortran mk_alpnum.f
./a.out <alpnum.txt
cp alpnum.str ~/lib


