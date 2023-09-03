#!/bin/bash

set -ex
for i in {3..1000}; do
    echo $i | ./a.out > /dev/null
done
