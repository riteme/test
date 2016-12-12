#include <cstdio>
#include <climits>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 7000000

typedef long long int64;

static int n, m;
static int64 q;
static int64 U, V;
static int t;
static int si, sa, sb;
static int ei, ea, eb;
static int64 qi[NMAX + 10];
static int64 qa[MMAX + 10];
static int64 qb[MMAX + 10];

static bool cmp(const int64 a, const int64 b) {
    return a > b;
}

static void initialize() {
    scanf("%d%d%lld%lld%lld%d", &n, &m, &q, &U, &V, &t);

    for (int i = 0; i < n; i++)
        scanf("%lld", qi + i);

    sort(qi, qi + n, cmp);
    ei = n;
    qi[n] = qa[0] = qb[0] = LLONG_MIN;
}

int main() {
    initialize();

    for (int cnt = 1; cnt <= m; cnt++) {
        int64 real;
        if (qa[sa] >= qi[si] && qa[sa] >= qb[sb])
            real = qa[sa++] + q * (cnt - 1);
        else if (qb[sb] >= qi[si] && qb[sb] >= qa[sa])
            real = qb[sb++] + q * (cnt - 1);
        else
            real = qi[si++] + q * (cnt - 1);

        int64 left = real * U / V;
        int64 right = real - left;
        qa[ea++] = left - q * cnt;
        qb[eb++] = right - q * cnt;

        if (cnt % t == 0)
            printf("%lld ", real);
    }

    printf("\n");
    qa[ea] = LLONG_MIN;
    qb[eb] = LLONG_MIN;

    int cnt = 1;
    while (si < ei || sa < ea || sb < eb) {
        int64 real;
        if (qa[sa] >= qi[si] && qa[sa] >= qb[sb])
            real = qa[sa++] + q * m;
        else if (qb[sb] >= qi[si] && qb[sb] >= qa[sa])
            real = qb[sb++] + q * m;
        else
            real = qi[si++] + q * m;

        if (cnt % t == 0)
            printf("%lld ", real);
        cnt++;
    }

    printf("\n");

    return 0;
}
