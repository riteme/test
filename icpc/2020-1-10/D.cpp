#include <cstdio>
#include <climits>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 4010

int n, K;
int w0[NMAX + 10], w1[NMAX + 10];
bool in[2 * NMAX + 10];
int d[2 * NMAX + 10];
int d0[NMAX + 10], d1[NMAX + 10];
int f[NMAX + 10][2];

void spfa() {
    queue<int> q;
    memset(d, 0x3f, sizeof(d));
    d[NMAX] = 0;
    q.push(NMAX);
    in[NMAX] = true;
    do {
        int u = q.front();
        q.pop();
        in[u] = false;

        for (int i = 1; i <= K; i++)
        if (u + i < NMAX + n && d[u + i] > d[u] + w0[i]) {
            d[u + i] = d[u] + w0[i];
            if (!in[u + i]) {
                in[u + i] = true;
                q.push(u + i);
            }
        }

        for (int i = 1; i <= K; i++)
        if (u - i > NMAX - n && d[u - i] > d[u] + w1[i]) {
            d[u - i] = d[u] + w1[i];
            if (!in[u - i]) {
                in[u - i] = true;
                q.push(u - i);
            }
        }
    } while (!q.empty());
}

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= K; i++)
        scanf("%d", w0 + i);
    for (int i = 1; i <= K; i++)
        scanf("%d", w1 + i);

    spfa();
    for (int i = 1; i < n; i++)
        d0[i] = d[NMAX + i];
    for (int i = 1; i < n; i++)
        d1[i] = d[NMAX - i];

    for (int i = 1; i < n; i++) {
        f[i][0] = f[i][1] = INT_MAX;
        for (int k = 1; k <= i; k++)
            f[i][0] = min(f[i][0], d0[k] + max(f[k - 1][1], f[i - k][0]));
        for (int k = 1; k <= i; k++)
            f[i][1] = min(f[i][1], d1[k] + max(f[i - k][1], f[k - 1][0]));
    }

    printf("%d\n", f[n - 1][0]);
    return 0;
}