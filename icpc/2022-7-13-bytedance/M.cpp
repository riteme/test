#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

constexpr int NMAX = 2000000;
constexpr int MMAX = 10000;
constexpr int SMAX = 26;

struct Node {
    int count = 0;
    int dp = 0;
    int fail = 0;
    int child[SMAX] = {0};
} m[NMAX + 10];
int mcnt = 1;

char buf[MMAX + 10];

int main() {
    int n;
    scanf("%d", &n);

    int root = 1;
    for (int i = 0; i < n; i++) {
        scanf("%s", buf);
        int u = root;
        for (int j = 0; buf[j]; j++) {
            int c = buf[j] - 'a';
            int &v = m[u].child[c];
            if (!v)
                v = ++mcnt;
            u = v;
        }
        m[u].count++;
    }

    queue<int> q;
    m[1].fail = 1;
    for (int c = 0; c < SMAX; c++) {
        int v = m[1].child[c];
        if (!v)
            continue;
        m[v].fail = 1;
        q.push(v);
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int c = 0; c < SMAX; c++) {
            int v = m[u].child[c];
            if (!v)
                continue;
            int y = m[u].fail;
            while (y != 1 && !m[y].child[c]) {
                y = m[y].fail;
            }
            if (m[y].child[c])
                y = m[y].child[c];
            m[v].fail = y;
            q.push(v);
        }
    }

    int ans = 0;
    q.push(1);
    m[1].dp = m[1].count;
    while (q.size()) {
        int u = q.front();
        ans = max(ans, m[u].dp);
        q.pop();
        for (int c = 0; c < SMAX; c++) {
            int v = m[u].child[c];
            if (!v)
                continue;
            m[v].dp = max(m[u].dp, m[m[v].fail].dp);
            m[v].dp += m[v].count;
            q.push(v);
        }
    }

    printf("%d\n", ans);
    return 0;
}
