#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 100

typedef long long int64;

static int64 n, t;
static int64 w[NMAX + 10];
static int64 v[NMAX + 10];

int main() {
    scanf("%lld%lld", &n, &t);

    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", w + i, v + i);
    }  // for

    int64 answer = 0;
    int64 sum = 0;
    for (int a = 1; a <= n; a++) {
        if (w[a] > t)
            continue;

        t -= w[a];
        sum += v[a];
        answer = max(answer, sum);

        for (int b = 1; b <= n; b++) {
            if (a == b || w[b] > t)
                continue;

            t -= w[b];
            sum += v[b];
            answer = max(answer, sum);

            for (int c = 1; c <= n; c++) {
                if (a == c || b == c || w[c] > t)
                    continue;

                t -= w[c];
                sum += v[c];
                answer = max(answer, sum);

                for (int d = 1; d <= n; d++) {
                    if (a == d || b == d || c == d || w[d] > t)
                        continue;

                    t -= w[d];
                    sum += v[d];
                    answer = max(answer, sum);

                    for (int e = 1; e <= n; e++) {
                        if (a == e || b == e || c == e || d == e || w[e] > t)
                            continue;

                        answer = max(answer, sum + v[e]);
                    }  // for

                    t += w[d];
                    sum -= v[d];
                }  // for

                t += w[c];
                sum -= v[c];
            }  // for

            t += w[b];
            sum -= v[b];
        }  // for

        t += w[a];
        sum -= v[a];
    }  // for

    printf("%lld\n", answer);

    return 0;
}  // function main
