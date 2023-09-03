set -ex

for n in {2..1000}; do
    for k in $(seq 1 2 $(($n - 1))); do
        echo "$n $k" | ./a.out
    done
done
