#!/bin/bash

cd build
rm -rf * && cmake ..
make clean all
./raylib_c_demo
