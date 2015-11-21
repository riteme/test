#include <cstdio>
#include <climits>
#include <cstring>
#include <cstdlib>

using namespace std;

#define NMAX 200000

static int G[NMAX + 10];
static int marked[NMAX + 10];

inline int read() {
    int n = 0;
    char c = getchar();
    while (c < '0' or c > '9') { c = getchar(); }  // while
    while ('0' <= c and c <= '9') {
        n = n * 10 + c - '0';
        c = getchar();
    }  // while
    return n;
}

int get_length(int v) {
    int length = 1;
    int e = v;

    for (v = G[v]; v != e; v = G[v]) { length++; }  // for

    return length;
}

int DFS(int v, int id) {
    int length = 1;

    int e = v;
    marked[v] = id;
    for (v = G[v]; marked[v] == 0; v = G[v]) {
        length++;
        marked[v] = id;
    }  // for

    if (marked[v] != id) { return INT_MAX; }

    if (v == e) { return length; } else {
        return get_length(v);
    }
}

int main() {
    int n = read();

    for (int i = 1; i <= n; i++) { G[i] = read(); }  // for

    int id = 1;
    int result = INT_MAX;
    for (int i = 1; i <= n; i++) {
        if (marked[i] == 0) {
            int l = DFS(i, id++);
            if (l < result) { result = l; }
        }
    }  // for

    printf("%d", result);

    return 0;
}  // function main
