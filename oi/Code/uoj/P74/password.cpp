#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>

using namespace std;

typedef long long int64;

inline int64 quick_pow(int64 a, int64 b, int64 m) {
    int64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }  // while

    return r;
}

inline int64 inv(int64 a, int64 p) {
    return quick_pow(a, p - 2, p);
}

#define NMAX 100000

static int n;
static int64 p;
static int64 h[NMAX + 10];

static void initialize() {
    scanf("%d%lld", &n, &p);

    for (int i = 0; i < n; i++) {
        scanf("%lld", h + i);
    }  // for
}

int main() {
    initialize();

    int64 inv1 = inv(quick_pow(26, n, p) - 1, p);
    if (inv1 < 0)  // Fuck: inverse less than zero!
        inv1 += p;

    if (inv1 > 0) {  // Big fuck: inverse becomes zero!!!!!!
        for (int i = 0; i < n; i++) {
            int64 c = ((h[i] * 26 % p - h[(i + 1) % n] % p) % p) * inv1 % p;
            if (c < 0)
                c += p;

            putchar(c + 'a');
        }  // for
    } else {
        // Strange idea......orz......
        stack<char> s;

        int64 target = h[0];
        for (int i = 0; i < n; i++) {
            s.push(target % 26);
            target /= 26;
        }  // for

        while (!s.empty()) {
            putchar(s.top() + 'a');
            s.pop();
        }  // while
    }

    return 0;
}  // function main
