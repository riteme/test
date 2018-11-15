#include <cstdio>
#include <cstring>

#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 8
#define MMAX 1000000
#define MOD 1000000007

typedef long long i64;
typedef unsigned long long u64;
typedef unordered_map<u64, i64> DP;

static int n, m;

int main() {
    scanf("%d%d", &n, &m);
    DP f, g;
    f[0] = 2;
    for (int i = 0; i < n + m - 2; i++) {
        g.clear();
        for (u64 s : f) {
        }
        swap(f, g);
    }
    return 0;
}
