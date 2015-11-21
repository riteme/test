#include <cstring>
#include <cstdio>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define L 2
#define MOD 10007
#define N 200010

struct P {
    P(int V, int D) {
        v = V;
        d = D;
    }

    int v;
    int d;
};  // struct P

static vector<int> G[N];
static int W[N];
static bool marked[N];
static int max = 0;
static int sum = 0;
static int n;

void BFS() {
    queue<P> p;

    for (int i = 1; i <= n; i++) {
        memset(marked, false, sizeof(bool) * N);

        marked[i] = true;
        p.push(P(i, 0));

        while (!p.empty()) {
            P v = p.front();
            p.pop();

            if (v.d == L) {
                int s = W[i] * W[v.v];
                sum = (sum + s) % MOD;

                if (::max < s) { ::max = s; }
            } else {
                for (vector<int>::iterator beg = G[v.v].begin();
                     beg != G[v.v].end();
                     beg++) {
                    if (!marked[*beg]) {
                        p.push(P(*beg, v.d + 1));
                        marked[*beg] = true;
                    }
                }  // for
            }

        }  // while

    }  // for
}

inline int Read(void) {
    int result = 0;

    char c;
    c = getchar();

    while (c == ' ' or c == '\n') { c = getchar(); }  // while

    while (c != ' ' and c != '\n') {
        result = result * 10 + (c - '0');
        c = getchar();
    }  // while

    return result;
}

int main() {
    // scanf("%d", &n);
    n = Read();

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        u = Read();
        v = Read();
        // scanf("%d %d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    for (int i = 1; i <= n; i++) {
        W[i] = Read();
        // scanf("%d", &W[i]);
    }  // for

    BFS();

    printf("%d %d", ::max, sum);

    return 0;
}  // function main
