#include <cstdio>
#include <cstring>

#include <algorithm>
#include <unordered_set>

using namespace std;

using u64 = unsigned long long;

constexpr u64 BASE = 0x19260817;

u64 H(const char *s, int n) {
	u64 ret = -1llu;

	for (int i = 0; i < n; i++) {
		u64 rax = 0;
		for (int j = 0; j < n; j++) {
			int k = (i + j) % n;
			rax = rax * BASE + s[k];
		}
		ret = min(ret, rax);
	}

	return ret;
}

char s[1000];

int main() {
	int n;
	scanf("%d", &n);
	unordered_set<u64> mp;
	while (n--) {
		scanf("%s", s);
		mp.insert(H(s, strlen(s)));
	}
	printf("%zu\n", mp.size());
	return 0;
}
