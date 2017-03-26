#!/bin/bash

NAME=icc

g++ -O2 -g -c -std=c++11 -static graderlib.cpp -o graderlib.o -lm 2>&1
fpc -XS -Xt -othe.exe grader.pas 2>&1
