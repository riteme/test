#include <cstdio>

int main() {
	int n, k;
	scanf("%d%d", &n, &k);

	bool ok = false;
	if (k == 1)
		ok = true;
	else if (k == 2)
		ok = n % 2 == 0;
	if (n == 4 && k == 3)
		ok |= true;
	puts(ok ? "Yes" : "No");

	return 0;
}
