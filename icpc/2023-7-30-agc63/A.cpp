#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 200000;

int n;
char S[NMAX + 10];

int main() {
	scanf("%d%s", &n, S);
	int acnt = 0, bcnt = 0;
	int j = 0;
	if (S[0] == 'A')
		acnt = 1;
	else
		bcnt = 1;
	for (int i = 0; i <= n; i++) {
		if (i > 0) {
			int a = (i + 1) / 2;
			int b = i / 2;
			while (j <= i && (S[j] != 'A' || a < bcnt || b >= acnt)) {
				// printf("i=%d j=%d a=%d acnt=%d b=%d bcnt=%d\n", i, j, a, acnt, b, bcnt);
				j++;
				if (S[j] == 'A')
					acnt++;
				else
					bcnt++;
			}
			bool awin = (j <= i);
			puts(awin ? "Alice" : "Bob");
		}
	}

	return 0;
}