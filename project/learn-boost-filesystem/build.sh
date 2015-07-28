#!/bin/bash
# compiler setting
COMPILER="clang++"
# COMPILER="g++"

# source code
SOURCE="./src/*.cpp"

# c++ setting
CXX_VERSION="c++14"
# CXX_STLLIB="libc++"
CXX_STLLIB=""  # using libc++ causes segfault on all boost::filesystem::path operations.

INCLUDE_PARAMS=""
LINK_PARAMS="-lboost_filesystem -lboost_system"
OTHER_PARAMS="-g -O0"

# compile command
if [ "$CXX_STLLIB" != "" ]; then
    $COMPILER -std=$CXX_VERSION -stdlib=$CXX_STLLIB $SOURCE $INCLUDE_PARAMS $LINK_PARAMS $OTHER_PARAMS
else
    $COMPILER -std=$CXX_VERSION $SOURCE $LINK_PARAMS $OTHER_PARAMS
fi
