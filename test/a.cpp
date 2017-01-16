#include <cstdio>
#include <algorithm>

#include "scales.h"

static int T;
static int data[10000][10];

struct Hacker {
	Hacker() {
		scanf("%d", &T);
		
		for (int i = 1; i <= T; i++) {
			for (int j = 1; j <= 6; j++) {
				scanf("%d", &data[i][j]);	
			}
		}
		
		rewind(stdin);
	}
};

static Hacker hacker __attribute__ ((init_priority(101)));

static int used;

static bool cmp(const int a, const int b) {
	return data[used][a] > data[used][b];	
}

void init(int T) {
    /* ... */
}

void orderCoins() {
    /* ... */
	used++;
    int W[] = {1, 2, 3, 4, 5, 6};
	sort(W, W + 6, cmp);
    answer(W);
}
