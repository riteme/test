#!/bin/bash
# source code
SOURCE="./src/*.cpp"

# c++ setting
CXX_VERSION="c++11"
CXX_ENABLE="all"

INCLUDE_PARAMS="-I/usr/include -I/usr/include/c++ -I/usr/include/c++/4.8"
OTHER_PARAMS=""

# cppcheck command
cppcheck --std=$CXX_VERSION --enable=$CXX_ENABLE $SOURCE $INCLUDE_PARAMS $OTHER_PARAMS
