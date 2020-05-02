n = 50000
print(999 + 3 * n)
for i in range(1000, 1999):
    print(f'{i}=alloc(100)')

for i in range(n):
    print('1999=alloc(100)')
    print('output(1999)')
    print('free(1999)')