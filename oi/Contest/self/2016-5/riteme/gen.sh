echo "Generating 1..."
./randomized-gen.py 1000 5000 > nuclear1.in

echo "Generating 2..."    
./circle-gen.py 10000 500000 > nuclear2.in 

echo "Generating 3..."
./circle-gen.py 100000 100 > nuclear3.in

echo "Generating 4..."
./randomized-gen.py 10000 1000000 > nuclear4.in

echo "Generating 5..."
./chain-gen.py 200000 1000000 > nuclear5.in

echo "Generating 6..."
./chain-gen.py 200000 1000000 > nuclear6.in

echo "Generating 7..."
./circle-gen.py 200000 1000000 > nuclear7.in

echo "Generating 8..."
./circle-gen.py 200000 1000000 > nuclear8.in

echo "Generating 9..."
./randomized-gen.py 200000 1000000 > nuclear9.in

echo "Generating 10..."
./randomized-gen.py 200000 1000000 > nuclear10.in

