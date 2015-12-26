// NOIP2014 寻找道路

#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef int ntype;

constexpr ntype NMAX = 10000;
constexpr auto FMT = "%d";
constexpr ntype INVAILD_VALUE = -1;

static ntype n, m;
static ntype s, t;
static ntype answer;
static vector<ntype> G[NMAX + 1];
static vector<ntype> GT[NMAX + 1];
static ntype dist[NMAX + 1];
static bool vaild[NMAX + 1];
static bool status[NMAX + 1];
static bool marked[NMAX + 1];

inline ntype read() {
    ntype x = 0;
    char c = getchar();
    while (c < '0' or c > '9') c = getchar();
    while ('0' <= c and c <= '9') x = x * 10 + (c - '0'), c = getchar();

    return x;
}

void initialize();
void quit();

void prepare_graph(const ntype e);
void remove_bad_nodes();

int main() {
    initialize();

    prepare_graph(t);
    memset(marked, false, sizeof(bool) * (n + 1));
    remove_bad_nodes();
    memset(marked, false, sizeof(bool) * (n + 1));

    if (vaild[s]) {
        queue<ntype> q;
        q.push(s);

        marked[s] = true;
        while (!q.empty()) {
            ntype u = q.front();
            q.pop();

            if (u == t and dist[u] < answer) answer = dist[u];

            for (auto v : G[u]) {
                if (vaild[v] and !marked[v]) {
                    q.push(v);
                    marked[v] = true;
                    dist[v] = dist[u] + 1;
                }
            }  // foreach in G[u]
        }      // while
    }

    if (answer == INT_MAX) answer = INVAILD_VALUE;

    quit();
    return 0;
}  // function main

void prepare_graph(const ntype e) {
    queue<ntype> q;
    q.push(e);

    marked[e] = status[e] = true;
    while (!q.empty()) {
        ntype u = q.front();
        q.pop();

        for (auto v : GT[u]) {
            if (!marked[v]) {
                marked[v] = status[v] = true;
                q.push(v);
            }
        }  // foreach in GT[u]
    }      // while
}

void remove_bad_nodes() {
    for (int u = 1; u <= n; u++) {
        if (!status[u]) {
            vaild[u] = false;

            for (auto v : GT[u]) vaild[v] = false;
        }
    }  // for
}

void initialize() {
    n = read();
    m = read();

    answer = INT_MAX;
    memset(vaild, true, sizeof(bool) * (n + 1));
    memset(status, false, sizeof(bool) * (n + 1));
    memset(marked, false, sizeof(bool) * (n + 1));
    memset(dist, 0, sizeof(ntype) * (n + 1));

    for (int cnt = 0; cnt != m; cnt++) {
        ntype x = read(), y = read();

        if (x != y) {
            G[x].push_back(y);
            GT[y].push_back(x);
        } else
            vaild[x] = false;  // Notice: node with self-loop is invaild.
    }                          // for

    s = read();
    t = read();
}

void quit() { printf(FMT, answer); }
