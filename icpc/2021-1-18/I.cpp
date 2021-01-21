#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

int buy(int x) {
	return x >= 500 ? x - 100 : x;
}

void chkmin(int &a, int b) {
	if (a > b)
		a = b;
}

int main() {
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);

	int ans = INT_MAX;
	chkmin(ans, buy(a) + buy(b) + buy(c));
	chkmin(ans, buy(a + b) + buy(c));
	chkmin(ans, buy(a + c) + buy(b));
	chkmin(ans, buy(a) + buy(b + c));
	chkmin(ans, buy(a + b + c));
	printf("%d\n", ans);

	return 0;
}
