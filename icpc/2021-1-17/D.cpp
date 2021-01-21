#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		i64 n, m, k;
		scanf("%lld%lld%lld", &n, &m, &k);

		i64 A = n - 1 - (m - 1) * k + m - 2;
		i64 B = m - 2;
		puts(((A & B) == B) ? "YES" : "NO");
	}
	return 0;
}
