#include <cstdio>
#include <cstring>
#include <climits>

#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 7000

static int cnt;
static unordered_map<i64, int> idx;
static i64 f[NMAX + 10], d[NMAX + 10];

void solve() {
    i64 n;
    scanf("%lld", &n);

    memset(f, 0, sizeof(f));
    memset(d, 0, sizeof(d));
    f[1] = 1;
    idx.clear();
    cnt = 0;
    for (i64 i = 1; i * i <= n; i++) {
	if (n % i)
	    continue;

	d[++cnt] = i;
	if (i * i != n)
	    d[++cnt] = n / i;
    }

    sort(d + 1, d + cnt + 1);

    for (int i = 1; i <= cnt; i++) {
	idx[d[i]] = i;
    }

    for (int i = 2; i < cnt; i++) {
	for (int j = cnt - 1; j >= 1; j--) {
	    if (d[i] * d[j] > n || n % (d[i] * d[j]))
		continue;
	    f[idx[d[i] * d[j]]] += f[j];
	}
    }

    printf("%lld\n", f[cnt] % 998244353);
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
	solve();
    }

    return 0;
}
