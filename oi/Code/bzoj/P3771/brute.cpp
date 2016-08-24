#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 200000

static int n;
static int seq[NMAX + 10];
static int cnt[NMAX + 10];

static int evaluate(int x) {
    int selected = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (x & (1 << i)) {
            sum += seq[i];
            selected++;
        }
    }  // for

    if (selected > 3)
        return 0;
    else
        return sum;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", seq + i);
    }  // for

    int bound = 1 << n;
    for (int i = 1; i < bound; i++) {
        int result = evaluate(i);

        if (result > 0) {
            cnt[result]++;
        }
    }  // for

    for (int i = 0; i < NMAX; i++) {
        if (cnt[i] > 0) {
            printf("%d %d\n", i, cnt[i]);
        }
    }  // for

    return 0;
}  // function main
