#!/bin/bash

g++ -DDISPLAY -I/usr/include/eigen3 algebra.cpp -o algebra.exe -std=c++17 `pkg-config eigen3 --cflags` `root-config --cflags --libs`
./algebra.exe
rm -r algebra.exe