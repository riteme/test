#include <cctype>
#include <cstring>
#include <climits>

#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 5000
#define MMAX 1000

static int n, m;
static string val[NMAX + 10];
static unordered_map<string, int> id;
static enum {
    AND, OR, XOR
} type[NMAX + 10];
static int lch[NMAX + 10], rch[NMAX + 10];
static bool marked[NMAX + 10];
static string minv, maxv;

#define OP(op) ((lb - '0') op (rb - '0')) + '0'

void dfs(int u, int pos) {
    if (marked[u])
        return;
    marked[u] = true;

    if (lch[u]) {
        dfs(lch[u], pos);
        dfs(rch[u], pos);

        char lb = val[lch[u]][pos];
        char rb = val[rch[u]][pos];
        switch (type[u]) {
            case AND: {
                val[u][pos] = OP(&);
            } break;

            case OR: {
                val[u][pos] = OP(|);
            } break;

            case XOR: {
                val[u][pos] = OP(^);
            } break;
        }
    }
}

int eval(int pos) {
    memset(marked, 0, sizeof(marked));

    for (int i = 1; i <= n + 1; i++) {
        if (!marked[i])
            dfs(i, pos);
    }

    int ret = 0;
    for (int i = 2; i <= n + 1; i++) {
        ret += val[i][pos] - '0';
    }

    return ret;
}

int main() {
    // freopen("data.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin >> n >> m;

    id["?"] = 1;
    string token;
    for (int i = 2; i <= n + 1; i++) {
        cin >> token;
        id[token] = i;
        cin >> token;
        cin >> token;

        if (isdigit(token[0]))
            val[i] = token;
        else {
            val[i].resize(m);
            lch[i] = id[token];

            cin >> token;
            if (token == "OR")
                type[i] = OR;
            else if (token == "AND")
                type[i] = AND;
            else
                type[i] = XOR;

            cin >> token;
            rch[i] = id[token];
        }
    }

    minv.resize(m);
    maxv.resize(m);
    val[1].resize(m);
    for (int i = 0; i < m; i++) {
        val[1][i] = '0';
        int zcnt = eval(i);
        val[1][i] = '1';
        int ocnt = eval(i);

        if (zcnt <= ocnt)
            minv[i] = '0';
        else
            minv[i] = '1';

        if (zcnt >= ocnt)
            maxv[i] = '0';
        else
            maxv[i] = '1';
    }

    cout << minv << endl << maxv << endl;

    return 0;
}
