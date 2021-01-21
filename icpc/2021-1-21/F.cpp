#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 100000;

int n;
int a[NMAX + 10];
int c[NMAX + 10];

bool check() {
	for (int i = 0; i < n; i++) {
		if (a[i] == 0)
			c[i] = c[i + 1] = 0;
		if (a[i] == 2)
			c[i] = c[i + 1] = 1;
		if (a[i] == 1)
			c[i + 1] = !c[i];
	}

	for (int i = 0; i < n; i++) {
		if (c[i] + c[i + 1] != a[i])
			return false;
	}

	return true;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", a + i);
	}

	c[0] = 0;
	bool ok = check();
	c[0] = 1;
	ok |= check();
	puts(ok ? "Yes" : "No");

	return 0;
}
