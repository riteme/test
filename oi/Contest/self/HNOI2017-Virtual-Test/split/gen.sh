# Subtask 1 x3 wh <= 2
echo 1
./gen.py 1 1 100 10 20 > split1.in
echo 2
./gen.py 2 1 100 10 20 > split2.in
echo 3
./gen.py 2 2 100 10 20 > split3.in

# Subtask 2 x3 wh <= 4
echo 4
./gen.py 2 4 1000000000 100000 100000 > split4.in
echo 5
./gen.py 3 3 1000000000 100000 1000 > split5.in
echo 6
./gen.py 4 3 1000000000 100000 100000 > split6.in

# Subtask 3 x4 wh <= 10
echo 7
./gen.py 4 4 1000000000 100000 100000 > split7.in
echo 8
./gen.py 9 9 1000000000 100000 1000 > split8.in
echo 9
./gen.py 10 9 1000000000 100000 100000 > split9.in
echo 10
./gen.py 10 10 1000000000 100000 100000 > split10.in

# Subtask 4 x5 wh <= 18
echo 11
./gen.py 2 18 1000000000 100000 100000 > split11.in
echo 12
./gen.py 16 16 1000000000 100000 1000 > split12.in
echo 13
./gen.py 17 17 1000000000 100000 100000 > split13.in
echo 14
./gen.py 18 18 1000000000 100000 100000 > split14.in
echo 15
./gen.py 18 18 1000000000 100000 100000 > split15.in

# Subtask 5 x5 wh <= 25
echo 16
./gen.py 20 20 1000000000 100000 100000 > split16.in
echo 17
./gen.py 21 21 1000000000 100000 1000 > split17.in
echo 18
./gen.py 23 22 1000000000 100000 100000 > split18.in
echo 19
./gen.py 24 25 1000000000 100000 100000 > split19.in
echo 20
./gen.py 25 1 1000000000 100000 100000 > split20.in

# Subtask 6 x10 wh <= 30
echo 21
./gen.py 25 25 1000000000 100000 100000 > split21.in
echo 22
./gen.py 30 2 1000000000 100000 1000 > split22.in
echo 23
./gen.py 1 30 1000000000 100000 100000 > split23.in
echo 24
./gen.py 1 1 1000000000 100000 100000 > split24.in
echo 25
./gen.py 27 27 1000000000 100000 100000 > split25.in
echo 26
./gen.py 30 30 1000000000 100000 1000 > split26.in
echo 27
./gen.py 30 30 1000000000 100000 100000 > split27.in
echo 28
./gen.py 30 30 1000000000 100000 100000 > split28.in
echo 29
./gen.py 30 30 1000000000 100000 100000 > split29.in
echo 30
./gen.py 30 30 1000000000 100000 100000 > split30.in

echo "Data generated."
