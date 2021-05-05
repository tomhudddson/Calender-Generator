#!/bin/bash

cd build
cmake ..
make -f Makefile
cd ..
cd bin
#./Calender_Generator.exe