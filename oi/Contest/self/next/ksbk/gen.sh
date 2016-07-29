echo "(info) Generating 'ksbk1.in'..."
./datagen.py 1000 1000 > ksbk1.in

echo "(info) Generating 'ksbk2.in'..."
./datagen.py 1000 1000 > ksbk2.in

echo "(info) Generating 'ksbk3.in'..."
./datagen.py 10000 100000 > ksbk3.in

echo "(info) Generating 'ksbk4.in'..."
./datagen.py 10000 200000 > ksbk4.in

echo "(info) Generating 'ksbk5.in'..."
./datagen.py 400000 1073741824 > ksbk5.in

echo "(info) Generating 'ksbk6.in'..."
./datagen.py 400000 8589934592 > ksbk6.in

echo "(info) Generating 'ksbk7.in'..."
./datagen.py 600000 4611686018427387904 > ksbk7.in

echo "(info) Generating 'ksbk8.in'..."
./datagen.py 600000 9223372036854775808 > ksbk8.in

echo "(info) Generating 'ksbk9.in'..."
./datagen.py 1000000 9223372036854775808 > ksbk9.in

echo "(info) Generating 'ksbk10.in'..."
./datagen.py 1800000 4911683098427387904 > ksbk10.in

echo "(info) Compiling standard program [g++ std.cpp -std=c++11 -o std.out -O2 -lm]..."
g++ std.cpp -std=c++11 -o std.out -O2 -lm

echo "(info) Generating 'ksbk1.out'..."
cp ksbk1.in ksbk.in
./std.out
mv ksbk.out ksbk1.out

echo "(info) Generating 'ksbk2.out'..."
cp ksbk2.in ksbk.in
./std.out
mv ksbk.out ksbk2.out

echo "(info) Generating 'ksbk3.out'..."
cp ksbk3.in ksbk.in
./std.out
mv ksbk.out ksbk3.out

echo "(info) Generating 'ksbk4.out'..."
cp ksbk4.in ksbk.in
./std.out
mv ksbk.out ksbk4.out

echo "(info) Generating 'ksbk5.out'..."
cp ksbk5.in ksbk.in
./std.out
mv ksbk.out ksbk5.out

echo "(info) Generating 'ksbk6.out'..."
cp ksbk6.in ksbk.in
./std.out
mv ksbk.out ksbk6.out

echo "(info) Generating 'ksbk7.out'..."
cp ksbk7.in ksbk.in
./std.out
mv ksbk.out ksbk7.out

echo "(info) Generating 'ksbk8.out'..."
cp ksbk8.in ksbk.in
./std.out
mv ksbk.out ksbk8.out

echo "(info) Generating 'ksbk9.out'..."
cp ksbk9.in ksbk.in
./std.out
mv ksbk.out ksbk9.out

echo "(info) Generating 'ksbk10.out'..."
cp ksbk10.in ksbk.in
./std.out
mv ksbk.out ksbk10.out
