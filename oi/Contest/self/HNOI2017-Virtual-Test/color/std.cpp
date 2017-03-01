// #define USE_FILE_IO

#define NAME "color"

#include <cstdio>
#include <cctype>
#include <cstring>

#define NMAX 60000000
#define MOD 1000000007
#define SMAX 16

typedef long long i64;

struct Result {
    Result() {
        memset(val, 0, sizeof(val));
    }

    i64 val[SMAX];

    void identity() {
        memset(val, 0, sizeof(val));
        val[0] = 1;
    }

    i64 &operator[](const int pos) {
        return val[pos];
    }

    const i64 operator[](const int pos) const {
        return val[pos];
    }

    friend Result operator*(const Result &a, const Result &b) {
        Result c;

        for (int i = 0; i < SMAX; i++) {
            for (int j = 0; j < SMAX; j++) {
                int k = i ^ j;
                c[k] += a[i] * b[j] % MOD;
                c[k] %= MOD;
            }
        }

        return c;
    }
};

inline Result quick_pow(Result a, int b) {
    Result r;
    r.identity();

    while (b) {
        if (b & 1)
            r = r * a;
        a = a * a;
        b >>= 1;
    }

    return r;
}

static int cnt[SMAX];
static int color[SMAX];

inline int to_int(char c) {
    if (isdigit(c))
        return c - '0';
    return c - 'A' + 10;
}

void initialize() {
    char c = getchar();
    while (isalnum(c)) {
        cnt[to_int(c)]++;
        c = getchar();
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    initialize();

    for (int i = 1; i < SMAX; i++) {
        for (int c = 0; true; c++) {
            bool flag = true;
            for (int j = i / 2; j < i && flag; j++) {
                if (color[j] == c)
                    flag = false;
            }

            if (flag) {
                color[i] = c;
                break;
            }
        }
    }

    Result initial;
    Result answer;
    answer.identity();

    for (int i = 0; i < SMAX; i++) {
        initial[color[i]]++;
        Result ret = quick_pow(initial, cnt[i]);
        answer = answer * ret;
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        int c;
        scanf("%d", &c);

        if (c <= SMAX)
            printf("%lld\n", answer[c - 1]);
        else
            printf("0\n");
    }

    return 0;
}
