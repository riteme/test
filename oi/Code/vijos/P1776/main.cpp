// NOIP2010 关押罪犯

#include <cstring>
#include <cstdio>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 20000
#define MMAX 100000
#define CMAX 1000000000

#define NONE (true + 10)
#define WHITE false
#define BLACK true

typedef int ntype;

struct Edge {
    Edge() : u(0), v(0), w(0) {}

    ntype u;
    ntype v;
    ntype w;

    ntype another(const ntype x) { return x == u ? v : u; }
};

static ntype n, m;
static ntype answer;
static vector<Edge *> G[NMAX + 10];
static Edge E[MMAX + 10];
static Edge *ptrE[MMAX + 10];
static char marked[NMAX + 10];

inline ntype read() {
    ntype x = 0;
    char c = getchar();
    while (c < '0' or c > '9') c = getchar();
    while ('0' <= c and c <= '9') x = x * 10 + (c - '0'), c = getchar();

    return x;
}

void initialize();
void quit();

bool check(const ntype x);

int main() {
    initialize();

    if (m == 0) {
        printf("0");

        return 0;
    }

    ntype l = 0, r = m;
    while (r - l > 1) {
        ntype mid = (l + r) / 2;
        answer = ptrE[mid]->w;
        // printf("answer = %d, l = %d, r = %d", answer, l, r);

        bool flag = check(answer);
        if (flag)
            r = mid;
        else
            l = mid;

        // printf(" ===> l = %d, r = %d\n", l, r);
    }

    if (l != r) {
        if (check(ptrE[l]->w))
            answer = ptrE[l]->w;
        else
            answer = ptrE[r]->w;
    } else
        answer = ptrE[l]->w;

    quit();
    return 0;
}  // function main

bool check(const ntype x) {
    memset(marked, NONE, sizeof(char) * (n + 1));

    queue<ntype> q;

    for (int i = 1; i <= n; i++) {
        if (marked[i] != NONE) continue;

        q.push(i);
        marked[i] = WHITE;

        while (!q.empty()) {
            ntype u = q.front();
            q.pop();

            for (int j = 0; j < G[u].size(); j++) {
                Edge *e = G[u][j];
                ntype v = e->another(u);

                if (e->w <= x) continue;

                if (marked[v] == NONE) {
                    marked[v] = !marked[u];

                    q.push(v);
                } else if (marked[v] == marked[u])
                    return false;
            }  // for
        }      // while

    }  // for

    return true;
}

bool compare(const Edge *a, const Edge *b);

bool compare(const Edge *a, const Edge *b) { return a->w < b->w; }

void initialize() {
    n = read();
    m = read();

    for (int i = 1; i <= m; i++) {
        E[i].u = read();
        E[i].v = read();
        E[i].w = read();

        if (E[i].u == E[i].v) continue;

        ptrE[i] = &E[i];
        G[E[i].u].push_back(ptrE[i]);
        G[E[i].v].push_back(ptrE[i]);
    }

    sort(ptrE + 1, ptrE + m + 1, compare);
    ptrE[0] = new Edge();
    ptrE[0]->w = 0;
}

void quit() { printf("%d", answer); }
