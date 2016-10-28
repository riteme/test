#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <stack>
#include <algorithm>

using namespace std;

#define NMAX 300000
#define MMAX 500000

typedef long long int64;

static int n, m;
static stack<int> edges;
static int father[NMAX + 10];
static int size[NMAX + 10];
static int ver;
static int64 answer[MMAX + 10];
static bool avaliable[MMAX + 10];

inline void initialize() {
    for (int i = 1; i <= n; i++) {
        size[i] = 1;
    }
}

inline int find_set(int x) {
    while (father[x])
        x = father[x];

    return x;
}

inline void union_set(int x, int y) {
    x = find_set(x);
    y = find_set(y);

    if (x == y) {
        edges.push(0);
        return;
    }

    if (size[x] < size[y]) {
        father[x] = y;
        size[y] += size[x];
        edges.push(x);
    } else {
        father[y] = x;
        size[x] += size[y];
        edges.push(y);
    }
}

inline void pop_edge() {
    size[father[edges.top()]] -= size[edges.top()];
    father[edges.top()] = 0;
    edges.pop();
}

static char command[MMAX + 10];
static int x[MMAX + 10], y[MMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    char buffer[10];

    for (int i = 1; i <= m; i++) {
        scanf("%s", buffer);

        command[i] = buffer[0];
        if (buffer[0] == 'A') {
            scanf("%d%d", x + i, y + i);
        } else if (buffer[0] == 'D') {
            scanf("%d", x + i);
        }
    }

    initialize();
    for (int i = 1; i <= m; i++) {
        bool fake = false;

        switch (command[i]) {
            case 'A': {
                union_set(x[i], y[i]);
                ver++;

                if (edges.top() == 0)
                    answer[ver] = answer[ver - 1];
                else
                    answer[ver] = answer[ver - 1] + i;
            } break;

            case 'D': {
                if (i < m && command[i + 1] == 'R') {
                    ver -= x[i];
                    fake = true;
                } else {
                    for (int j = 0; j < x[i]; j++) {
                        pop_edge();
                        ver--;
                    }
                }
            } break;

            case 'R': {
                if (command[i - 1] == 'A') {
                    pop_edge();
                    ver--;
                } else {
                    ver += x[i - 1];
                    fake = true;
                }
            } break;
        }

        if (!fake) {
            if (size[find_set(1)] == n)
                avaliable[ver] = true;
            else
                avaliable[ver] = false;
        }

        if (avaliable[ver])
            printf("%lld\n", answer[ver]);
        else
            puts("0");
    }
}
