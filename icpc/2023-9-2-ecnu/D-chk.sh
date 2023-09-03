#!/bin/bash

set -e

for i in {1..1000}; do
    echo $i
    python D-gen.py > D0.in
    ./a.out < D0.in > D0.out
    ./b.out < D0.in > D0.ans
    diff -Bb D0.out D0.ans
done
