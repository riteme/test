#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 10000

static int n, m;
static int parent[NMAX + 10];
static int left[NMAX + 10];
static int right[NMAX + 10];
static bool reversed[NMAX + 10];

static void pushdown(int x) {
    if (x > 0 && reversed[x]) {
        swap(left[x], right[x]);
        reversed[left[x]] ^= true;
        reversed[right[x]] ^= true;
    }
}

static void left_rotate(int x) {
    assert(x > 0);
    assert(left[x] > 0);
    assert(!reversed[x]);
    assert(!reversed[left[x]]);

    int y = left[x];
    left[x] = right[y];
    if (left[x] > 0)
        parent[left[x]] = x;
    right[y] = x;
}

int main() {
    memset(parent, 0, sizeof(parent));
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    memset(reversed, 0, sizeof(reversed));
    scanf("%d%d", &n, &m);

    return 0;
}  // function main
