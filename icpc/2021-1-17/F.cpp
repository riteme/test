#include <cstdio>
#include <cstring>

#include <map>
#include <algorithm>

using namespace std;

using i64 = long long;
using pii = pair<i64, i64>;

constexpr int NMAX = 30000000;

int n, m;
i64 P, Q, B, C, MOD;
i64 a[NMAX + 10];

pii get(i64 x) {
	i64 l = (P * x + Q - 1) / Q;
	i64 r = (Q * x) / P;
	return {l, r};
}

int main() {
	scanf("%d%lld%lld", &n, &P, &Q);
	scanf("%d%lld%lld%lld", &m, &B, &C, &MOD);
	for (int i = 1; i <= m; i++) {
		scanf("%lld", a + i);
	}

	map<i64, int> id;
	bool found = false;
	for (int i = 1; i <= n; i++) {
		i64 v = i <= m ? a[i] : ((B * a[i - 1] + C) % MOD + 1);
		pii ran = get(v);
		auto it = id.lower_bound(ran.first);
		if (it != id.end() && it->first <= ran.second) {
			found = true;
			printf("%d %d\n", it->second, i);
			break;
		}

		a[i] = v;
		id[v] = i;
	}

	if (!found)
		puts("-1");

	return 0;
}
