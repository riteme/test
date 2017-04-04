#include <cstdio>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 10000000
#define MOD 577777777

typedef long long i64;

static bool marked[NMAX + 10];
static int cnt;
static int primes[NMAX + 10];
static int n;

void initialize() {
    scanf("%d", &n);

    for (int i = 2; i <= NMAX; i++) {
        if (!marked[i])
            primes[++cnt] = i;
        if (cnt > n)
            break;
        
        for (int j = 1; j <= cnt && i * primes[j] <= NMAX; j++) {
            int p = primes[j];
            marked[i * p] = true;

            if (i % p == 0)
                break;
        }
    }
}

struct cmp {
    bool operator()(const i64 a, const i64 b) const {
        return a > b;
    }
};

int main() {
    initialize();

    priority_queue<i64, vector<i64>, cmp> q;
    for (int i = 1; i <= cnt; i++) {
        q.push(primes[i]);
    }

    i64 answer = 1;
    while (n--) {
        i64 minv = q.top();
        q.pop();
        q.push(minv * minv);
        answer = answer * minv % MOD;
    }

    printf("%lld\n", answer);

    return 0;
}
