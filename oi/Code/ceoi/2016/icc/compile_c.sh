#!/bin/bash

NAME=icc

gcc -static -std=gnu11 -O2 -c -o $NAME.o $NAME.c -lm 2>&1
g++ -O2 -std=c++11 -static grader.cpp icc.o -o the.exe -lm 2>&1
