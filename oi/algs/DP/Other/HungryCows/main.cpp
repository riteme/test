// 70: WA

#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 2000
#define BMAX 1000

static int n, b;
static int element_count = 0;
static int f[NMAX + 10];
static int s[BMAX + 10];
static int list_first[NMAX + 10];
static int list_node_next[BMAX + 10];

inline void list_push(int p, int x) {
    list_node_next[x] = list_first[p];
    list_first[p] = x;
}

inline void read() {
    int u, v;
    cin >> u >> v;

    s[++element_count] = u;
    list_push(v, element_count);

    if (n < v) n = v;
}

int main() {
    ios::sync_with_stdio(false);

    memset(f, 0, sizeof(f));
    memset(list_first, -1, sizeof(list_first));
    memset(list_node_next, -1, sizeof(list_node_next));

    cin >> b;
    for (int i = 0; i < b; i++) read();

    for (int i = 1; i <= n; i++) {
        int x = list_first[i];

        while (x != -1) {
            int length = i - s[x] + 1;
            f[i] = std::max(f[i], f[i - length] + length);

            x = list_node_next[x];
        }  // while

        f[i] = std::max(f[i - 1], f[i]);
    }  // for

    cout << f[n];

    return 0;
}  // function main
