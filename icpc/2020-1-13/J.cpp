#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n = 5;
int in[100];
vector<int> G[100];
char s[100];

void link(int u, int v) {
    in[v]++;
    G[u].push_back(v);
}

int topo[100], m;

int main() {
    for (int i = 0; i < 5; i++) {
        scanf("%s", s);
        if (s[1] == '>')
            link(s[0] - 'A' + 1, s[2] - 'A' + 1);
        else
            link(s[2] - 'A' + 1, s[0] - 'A' + 1);
    }

    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!in[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        topo[++m] = u;
        q.pop();
        for (int v : G[u]) {
            in[v]--;
            if (!in[v]) q.push(v);
        }
    }

    if (m < n) puts("impossible");
    else {
        for (int i = n; i >= 1; i--)
            putchar('A' + topo[i] - 1);
        puts("");
    }
    return 0;
}