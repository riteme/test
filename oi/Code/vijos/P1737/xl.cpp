#include <cstdio>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define KMAX 50

typedef long long int64;

static int n, k, p;
static int color[NMAX + 10];
static int price[NMAX + 10];
static int right[NMAX + 10];
static int pre[KMAX + 10][NMAX + 10];

static void initialize() {
    scanf("%d%d%d", &n, &k, &p);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", color + i, price + i);

        pre[color[i]][i] = 1;
    }

    for (int i = 0; i < k; i++)
        for (int j = 1; j <= n; j++)
            pre[i][j] += pre[i][j - 1];

    int j = 1;
    deque<int> q;
    price[n + 1] = -1;
    for (int i = 1; i <= n; i++) {
        j = max(i, j);
        while (j <= n + 1 && (q.empty()) || price[q.front()] > p) {
            while (!q.empty() && price[q.back()] > price[j])
                q.pop_back();

            q.push_back(j);
            j++;
        }

        right[i] = q.front();

        if (q.front() == i)
            q.pop_front();
    }
}

int main() {
    initialize();
    
    int64 answer = 0;
    for (int i = 1; i <= n; i++)
        answer += pre[color[i]][n] - pre[color[i]][max(i + 1, right[i]) - 1];

    printf("%lld\n", answer);
    return 0;
}
