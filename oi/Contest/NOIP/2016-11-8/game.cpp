#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long int64;

static int n, m;
static int64 h[NMAX + 10];
static int64 fucked = 0;

inline int64 get(int i) {
    return h[i] - fucked;
}

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++)
        scanf("%lld", h + i);

    sort(h + 1, h + n + 1);

    int64 answer = 0;
    for (int i = 1; i <= n && m > 0; i++) {
        if (get(i) <= 0)
            continue;

        if (get(i) == 1) {
            int j = i;
            while (get(j + 1) == get(i))
                j++;
            answer += n - j;
            fucked++;
            m--;
        } else if (i == n - 1) {
            h[i] -= 2;
            
            if (get(i) <= 0)
                answer++;
            else
                answer += 2;

            m--;
            i--;
        } else if (i == n) {
            h[i] -= 2;

            if (get(i) > 0)
                answer++;

            m--;
            i--;
        } else {
            fucked++;
            answer += n - i + 1;
            m--;
            i--;
        }
    }
    
    int64 alive = n;
    for (int i = 1; i <= n; i++) {
        if (get(i) > 0)
            answer += (alive - 1) * get(i) + get(i) - 1;
        alive--;
    }

    printf("%lld\n", answer);
    return 0;
}
