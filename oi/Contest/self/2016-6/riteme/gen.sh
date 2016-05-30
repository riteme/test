echo "(info) Generating sequences..."
echo "    * Generating 1..."
./chain-gen-2.py 20000 > seq1

echo "    * Generating 2..."
./fold-gen.py 90000 > seq2

echo "    * Generating 3..."
./heavy-chain-gen.py 100000 > seq3

echo "    * Generating 4..."
./divide-gen.py 100000 > seq4

echo "    * Generating 5..."
./chain-gen-1.py 200000 > seq5

echo "    * Generating 6..."
./divide-gen.py 200000 > seq6

echo "    * Generating 7..."
./fold-gen.py 200000 > seq7

echo "    * Generating 8..."
./heavy-chain-gen.py 200000 > seq8

echo "    * Generating 9..."
./more-heavy-chain-gen.py 200000 > seq9

echo "    * Generating 10..."
./randomized-gen.py 200000 > seq10

echo "(info) Packaging sequences..."
echo "(info) Compiling packer..."
gcc packer.c -O3 -std=c11 -o packer
./packer seq1 bst1.in
echo "    * 10% Completed."

./packer seq2 bst2.in
echo "    * 20% Completed."

./packer seq3 bst3.in
echo "    * 30% Completed."

./packer seq4 bst4.in
echo "    * 40% Completed."

./packer seq5 bst5.in
echo "    * 50% Completed."

./packer seq6 bst6.in
echo "    * 60% Completed."

./packer seq7 bst7.in
echo "    * 70% Completed."

./packer seq8 bst8.in
echo "    * 80% Completed."

./packer seq9 bst9.in
echo "    * 90% Completed."

./packer seq10 bst10.in
echo "    * 100% Completed."

echo "(info) Cleaning up..."
rm seq*
