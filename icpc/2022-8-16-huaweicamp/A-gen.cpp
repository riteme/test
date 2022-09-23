#include "testlib.h"
#include <set>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
#define mp make_pair

const int SumN = 100000, SumM = 1000000;
//const int SumN = 100, SumM = 1000;

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);
	int N = atoi(argv[1]), M = atoi(argv[2]), L = atoi(argv[3]);
	//int N = 5, M = 5, L = 5;

	int T = min(SumN / (N + M), SumM / ((N + M) * L));
	for (printf("%d\n", T); T; T --)
	{
		int n = rnd.next(2, N);
		int m = rnd.next(1, M);
		printf("%d %d\n", n, m);
		for (int i = 1; i <= n + m; i ++)
		{
			for (int l = rnd.next(1, L); l; l --)
				putchar('0' + rnd.next(0, 1));
			puts("");
		}
	}

	return 0;
}
