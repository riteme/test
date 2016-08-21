#include <bits/stdc++.h>

using namespace std;

#define LINEAR_ALGO_MAX 100000

typedef long long int64;

static int pcnt;
static int prime[LINEAR_ALGO_MAX + 10];
static bool marked[LINEAR_ALGO_MAX + 10];
static int miu[LINEAR_ALGO_MAX + 10];
static void compute_primes() {
    marked[1] = true;
    miu[1] = 1;

    for (int i = 2; i <= LINEAR_ALGO_MAX; i++) {
        if (!marked[i]) {
            prime[++pcnt] = i;
            miu[i] = -1;
        }

        for (int j = 1; j <= pcnt && prime[j] * i <= LINEAR_ALGO_MAX; j++) {
            int p = prime[j];
            marked[p * i] = true;

            if (i % p == 0) {
                miu[i * p] = 0;
                break;
            } else
                miu[i * p] = miu[i] * miu[p];
        }  // for
    }      // for
}

static int test(int x) {
    int answer = 0;

    for (int i = 1; i * i <= x; i++) {
        answer += x / (i * i) * miu[i];
    }  // for

    return answer;
}

int main() {
    compute_primes();

    int t;
    scanf("%d", &t);

    while (t--) {
        int k;
        scanf("%d", &k);

        int left = 1, right = k * 2;
        while (left + 1 < right) {
            int mid = (int64(left) + int64(right)) /
                      2;  // Caution: int overflow while `left + right`

            if (test(mid) >= k)
                right = mid;
            else
                left = mid;
        }  // while

        if (left != right && test(left) < k)
            left = right;

        printf("%d\n", left);
    }  // while

    return 0;
}  // function main
