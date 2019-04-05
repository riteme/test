#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 500000

static int A[300], B[300];
static char T[NMAX + 10];
static int nxt[NMAX + 10];

int main() {
	scanf("%s", T);
	for (int i = 0; T[i]; i++) A[T[i]]++;
	scanf("%s", T + 1);
	for (int i = 1; T[i]; i++) B[T[i]]++;
	nxt[1] = 0;
	int j = 0;
	for (int i = 2; T[i]; i++) {
		while (j && T[j + 1] != T[i]) j = nxt[j];
		if (T[j + 1] == T[i]) j++;
		nxt[i] = j;
	}
	fprintf(stderr, "j = %d\n", j);
	bool first = true;
	while (A['0'] || A['1']) {
		if (A['0'] >= B['0'] && A['1'] >= B['1']) {
			A['0'] -= B['0'];
			A['1'] -= B['1'];
			if (first) {
				printf("%s", T + 1);
				for (int i = 1; i <= j; i++) B[T[i]]--;
				first = false;
			} else printf("%s", T + j + 1);
		} else if (A['0']) {
			putchar('0');
			A['0']--;
		} else {
			putchar('1');
			A['1']--;
		}
	}
	puts("");
	return 0;
}
