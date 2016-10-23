#!/usr/bin/env sh

echo "Generating \"money1.in\"..."
./datagen.py 5 5 1 5 > money1.in

echo "Generating \"money2.in\"..."
./datagen.py 10 20 1 10 > money2.in

echo "Generating \"money3.in\"..."
./datagen.py 20 50 2 4 > money3.in

echo "Generating \"money4.in\"..."
./datagen.py 10000 100 6000 6000 > money4.in

echo "Generating \"money5.in\"..."
./datagen.py 100000 100 60000 60000 > money5.in

echo "Generating \"money6.in\"..."
./datagen.py 1000000 100 600000 600000 > money6.in

echo "Generating \"money7.in\"..."
./datagen.py 600000 100 233 600000 > money7.in

echo "Generating \"money8.in\"..."
./datagen.py 700000 100 244 700000 > money8.in

echo "Generating \"money9.in\"..."
./datagen.py 900000 100 255 900000 > money9.in

echo "Generating \"money10.in\"..."
./datagen.py 1000000 100 266 1000000 > money10.in
