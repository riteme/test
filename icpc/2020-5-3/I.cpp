#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 4000
#define SIZE 9901

typedef long long i64;

struct item {
    int key, val;
};

vector<item> buc[SIZE];

void insert(int key, int val) {
    int pos = key % SIZE;
    buc[pos].push_back({key, val});
}

int query(int key) {
    int pos = key % SIZE;
    for (auto &e : buc[pos])
    if (e.key == key)
        return e.val;
    return 0;
}

int L, M, n;
int A[NMAX + 10], B[NMAX + 10];

int go(i64 i, i64 k) {
    i = i64(i + k) % M;
    if (i < 0) i += M;
    return i < L ? i : M - i - 1;
}

bool mark[NMAX * 2 + 10];
int deg[NMAX * 2 + 10];
vector<int> G[NMAX * 2 + 10];

void link(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
    deg[u]++;
    deg[v]++;
}

bool test(i64 K) {
    memset(mark + 1, 0, 2 * n);
    memset(deg + 1, 0, sizeof(int) * 2 * n);
    for (int i = 1; i <= 2 * n; i++) {
        G[i].clear();
        // G[i].shrink_to_fit();
    }

    for (int i = 1; i <= n; i++) {
        int p = go(A[i], K);
        int v = query(p);
        if (v)
            link(i, n + v);

        p = go(A[i], -K);
        v = query(p);
        if (v)
            link(i, n + v);
    }

    queue<int> q;
    for (int i = 1; i <= 2 * n; i++)
    if (deg[i] == 0)
        return false;
    else if (deg[i] == 1)
        q.push(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (mark[u])
            continue;

        mark[u] = true;

        int v = 0;
        for (int i : G[u]) if (!mark[i]) {
            v = i;
            break;
        }
        if (!v)
            return false;
        // assert(v);

        mark[v] = true;
        for (int i : G[v]) if (!mark[i]) {
            deg[i]--;
            if (deg[i] == 0)
                return false;
            else if (deg[i] == 1)
                q.push(i);
        }
    }

    return true;
}

int main() {
    scanf("%d%d", &L, &n);
    M = 2 * L;
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        A[i]--;
        // printf("%d ", go(A[i], (i & 1 ? 1 : -1) * 998244353) + 1);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", B + i);
        B[i]--;
        insert(B[i], i);
    }

    int ans = INT_MAX;
    // for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
        i64 x = A[1], y = B[j];
        i64 p[] = {
            y, M - y - 1,
            -y - 1,
            -(M - y - 1) - 1
        };
        for (int k = 0; k < 4; k++) {
            i64 len = abs(p[k] - x);
            if (len < ans && test(len))
                ans = len;
        }
    }
    if (ans == INT_MAX)
        ans = -1;
    printf("%d\n", ans);

    return 0;
}