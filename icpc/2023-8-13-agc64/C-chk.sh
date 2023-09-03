#!/bin/bash

set -ex

# while [ true ]; do
for i in {1..1000}; do
    echo -e "1\n2\n0 $(($i - 1))\n$(($i + 1)) 1001" > C.in
    # python C-gen.py > C.in
    ./a.out < C.in > C.out
    ./b.out < C.in > C.ans
    diff -Bb C.out C.ans
done
