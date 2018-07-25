//  Created by Sengxian on 09/09/16.
//  Copyright (c) 2016年 Sengxian. All rights reserved.
//  BZOJ 1086 树分块
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
inline int ReadInt() {
    static int n, ch;
    n = 0, ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) n = (n << 3) + (n << 1) + ch - '0', ch = getchar();
    return n;
}

const int MAX_N = 1000 + 3;
vector<int> G[MAX_N];
int n, B, stk[MAX_N], sz = 0;
int block_cnt = 0, province[MAX_N], bel[MAX_N];

void dfs(int u, int fa = -1) {
    int bottom = sz;
    for (int i = 0; i < (int)G[u].size(); ++i) {
        int v = G[u][i];
        if (v == fa) continue;
        dfs(v, u);
        if (sz - bottom >= B) {
            while (sz != bottom) {
                bel[stk[--sz]] = block_cnt;
            }
            province[block_cnt++] = u;
        }
    }
    stk[sz++] = u;
}

int main() {
    n = ReadInt(), B = ReadInt();
    for (int i = 0, f, t; i < n - 1; ++i) {
        f = ReadInt() - 1, t = ReadInt() - 1;
        G[f].push_back(t), G[t].push_back(f);
    }
    dfs(0);
    while (sz) bel[stk[--sz]] = block_cnt - 1;
    printf("%d\n", block_cnt);
    for (int i = 0; i < n; ++i)
        printf("%d%c", bel[i] + 1, i + 1 == n ? '\n' : ' ');
    for (int i = 0; i < block_cnt; ++i)
        printf("%d%c", province[i] + 1, i + 1 == block_cnt ? '\n' : ' ');
    return 0;
}

