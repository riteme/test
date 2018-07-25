#include <cstdio>

#include <algorithm>

using namespace std;

inline int gcd(int a, int b) {
    while (b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }

    return a;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);

        int size = a * b * 2;
        int covered;

        if (c <= a && c <= b)
            covered = c * c;
        else if (c <= a && c > b)
            covered = c * c - (c - b) * (c - b); 
        else if (c > a && c <= b)
            covered = c * c - (c - a) * (c - a);
        else if (a + b >= c)
            covered = size - (a + b - c) * (a + b - c);
        else
            covered = size;

        int factor = gcd(size, covered);
        printf("%d/%d\n", covered / factor, size / factor);
    }

    return 0;
}
