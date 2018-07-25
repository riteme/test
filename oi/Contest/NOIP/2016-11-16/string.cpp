#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000

typedef long long int64;

inline int gcd(int a, int b) {
    while (b) {
        int tmp = a;
        a = b;
        b = tmp % b;
    }

    return a;
}

static int64 n, m;
static char S[NMAX + 10];
static char T[NMAX + 10];
static int f[NMAX + 10][26];

int main() {
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    scanf("%s%s", S, T);
    
    int64 answer = 0;
    int slen = strlen(S), tlen = strlen(T);
    int step = gcd(slen, tlen);
    for (int i = 0; i < tlen; i++) {
        f[i][T[i] - 'a']++;

        if (i - step >= 0) {
            for (int j = 0; j < 26; j++)
                f[i][j] += f[i - step][j];
        }
    }

    for (int i = 0; i < slen; i++) {
        int endpoint = tlen - step + (i % step);
        answer += f[endpoint][S[i] - 'a'];
    }

    printf("%lld\n", answer * (n / tlen) * step);
}
