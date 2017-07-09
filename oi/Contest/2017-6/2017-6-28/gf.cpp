#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 500000

typedef long long i64;

static int n;
static int seq[NMAX + 10];
static i64 f0, k0;
typedef greater<int> cmp;
static priority_queue<int, vector<int>, cmp> func;

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
    }
}

void popleft() {
    i64 x = 0;
    while (k0 < 0) {
        f0 += (func.top() - x) * k0;
        x = func.top();
        k0++;
        func.pop();
    }
}

int main() {
    initialize();

    for (int i = 1; i <= n; i++) {
        popleft();
        f0 += seq[i];
        k0 = -1;
        func.push(seq[i]);
        func.push(seq[i]);
    }

    popleft();
    printf("%lld\n", f0);

    return 0;
}
