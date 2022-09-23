#include <cstdio>
#include <cstring>

#include <queue>
#include <random>
#include <algorithm>

using namespace std;

// constexpr int NMAX = 100000;
constexpr int LMAX = 1000000;
constexpr int CMAX = 2;

struct Node {
    int i;
    int mark;
    int fail;
    int ch[CMAX];
    int go[CMAX];
};

int n, m, cnt;
char s[LMAX + 10];
Node no[LMAX + 10];
bool vis[LMAX + 10];
bool ok[LMAX + 10];

void bfs(std::queue<int> &q) {
    while (q.size()) {
        int x = q.front();
        q.pop();
        for (int c = 0; c < CMAX; c++) {
            int y = no[x].go[c];
            if (no[y].mark > n + 1)
                continue;
            if (!vis[y]) {
                vis[y] = true;
                q.push(y);
            }
        }
    }
}

int add(char *s) {
    int x = 1;
    for (int i = 0; s[i]; i++) {
        int c = s[i] - '0';
        int &y = no[x].ch[c];
        if (!y) {
            y = ++cnt;
            memset(no + y, 0, sizeof(no[y]));
        }
        x = y;
    }
    return x;
}

int meld(int u, int v) {
    if (u == -1)
        return v;
    if (v == -1)
        return v;
    if (u > n || v > n)
        return max(u, v);
    else if (u < 0 || v < 0)
        return n + 1;
    else if (u > 0 && v > 0 && u != v)
        return n + 1;
    else
        return max(u, v);
}

void build() {
    queue<int> q;
    no[1].fail = 1;
    for (int c = 0; c < CMAX; c++) {
        int y = no[1].ch[c];
        if (y) {
            no[1].go[c] = y;
            q.push(y);
            no[y].fail = 1;
            no[y].mark = no[y].i;
        } else {
            no[1].go[c] = 1;
        }
    }

    while (q.size()) {
        int x = q.front();
        q.pop();
        for (int c = 0; c < CMAX; c++) {
            int y = no[x].ch[c];
            if (y) {
                no[x].go[c] = y;
                q.push(y);

                int z = no[x].fail;
                while (z != 1 && !no[z].ch[c]) {
                    z = no[z].fail;
                }
                if (no[z].ch[c])
                    z = no[z].ch[c];
                no[y].fail = z;

                no[y].mark = meld(no[y].i, no[z].mark);
                // no[y].mark = meld(no[y].mark, no[x].mark);
            } else {
                no[x].go[c] = no[no[x].fail].go[c];
            }
        }
    }
}

bool solve(int t) {
    scanf("%d%d", &n, &m);
    // if (t == 180) {
    //     fprintf(stderr, "%d %d\n", n, m);
    // }
    cnt = 1;
    memset(no + 1, 0, sizeof(no[1]));
    for (int i = 1; i <= n; i++) {
        scanf("%s", s);
        // if (t == 180) {
        //     fputs(s, stderr);
        //     fputc('\n', stderr);
        // }
        int x = add(s);
        no[x].i = meld(no[x].i, i);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%s", s);
        // if (t == 180) {
        //     fputs(s, stderr);
        //     fputc('\n', stderr);
        // }
        int x = add(s);
        no[x].i = meld(no[x].i, n + 1 + i);
    }

    build();

    queue<int> q;
    memset(vis + 1, 0, cnt);
    q.push(1);
    vis[1] = true;
    bfs(q);
    memcpy(ok + 1, vis + 1, cnt);
    for (int x = 2; x <= cnt; x++) {
        if (ok[x] && no[x].mark == n + 1)
            return true;
    }

    std::mt19937 gen(0x19260817);
    for (int k = 0; k < 20; k++) {
        memset(vis + 1, 0, cnt);
        unsigned int seed = gen();
        for (int x = 2; x <= cnt; x++) {
            unsigned int v = no[x].mark;
            if (ok[x] && v && ((v * seed % 97) & 1) == 1) {
                q.push(x);
                vis[x] = true;
            }
        }

        bfs(q);

        for (int x = 2; x <= cnt; x++) {
            unsigned int v = no[x].mark;
            if (ok[x] && v && ((v * seed % 97) & 1) != 1 && vis[x])
                return true;
        }
    }

    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        puts(solve(t) ? "Yes" : "No");
    }
    return 0;
}
