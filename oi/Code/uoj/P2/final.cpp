// AC

#include <cstdio>
#include <cstring>
#include <bitset>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define LMAX 32

typedef unsigned long ntype;

int main() {
    int n;
    ntype m;

    scanf("%d %ld", &n, &m);

    bitset<LMAX> zero("00000000000000000000000000000000");
    bitset<LMAX> one("11111111111111111111111111111111");
    char buf[4];
    ntype v;

    // O(n)
    for (ntype i = 1; i <= n; i++) {
        scanf("%s %ld", buf, &v);

        if (strcmp(buf, "OR") == 0) {
            zero |= v;
            one |= v;
        } else if (strcmp(buf, "AND") == 0) {
            zero &= v;
            one &= v;
        } else {  // XOR
            zero ^= v;
            one ^= v;
        }
    }  // for

    // O(1)
    int k;
    bitset<LMAX> ruler(m);
    for (k = LMAX - 1; k >= 0 and !ruler.test(k); k--) {}  // for

    ntype max = 0;

    ntype tm = 0;
    for (int i = 29; i >= 0; i--) {
        max <<= 1;
        tm <<= 1;
        bool g = zero[i];

        if (i == k) {
            if (one[i] > g) {
                g = true;
                tm += 1;
            }
        } else if (i < k) {
            if (tm + 1 <= (m >> i) and one[i] > g) {
                g = one[i];
                tm += 1;
            }
        }

        max += g;
    }  // for

    printf("%ld", max);

    return 0;
}  // function main
