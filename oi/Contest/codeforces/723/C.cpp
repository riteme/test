#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 2000

static int n, m;
static int A[NMAX + 10];
static int cnt[NMAX + 10];
static int target[NMAX + 10];
static int seq[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
    }  // for
}

int main() {
    initialize();
    int answer1 = n / m;

    for (int i = 1; i <= n; i++) {
        if (A[i] <= m)
            cnt[A[i]]++;
    }  // for

    int remain = n % m;
    while (remain > 0) {
        int maxpos = 0;
        for (int i = 1; i <= m; i++) {
            if (target[i])
                continue;

            if (cnt[i] >= cnt[maxpos])
                maxpos = i;
        }  // for

        if (cnt[maxpos] <= answer1) {
            target[maxpos] = answer1;
            remain -= answer1 - cnt[maxpos];
            break;
        } else if (cnt[maxpos] <= answer1 + remain) {
            target[maxpos] = cnt[maxpos];
            remain = answer1 + remain - cnt[maxpos];
        } else {
            cnt[maxpos] = answer1 + remain;
            break;
        }
    }  // while

    for (int i = 1; i <= m; i++) {
        if (target[i] == 0)
            target[i] = answer1;
    }  // for

    for (int i = 1; i <= m; i++) {
        seq[i] = i;
    }  // for

    sort(seq + 1, seq + m + 1, [](const int a, const int b) {
        return cnt[a] - target[a] < cnt[b] - target[b];
    });

    int answer2 = 0;
    for (int i = 1; i <= m; i++) {
        int current = seq[i];

        while (cnt[current] < target[current]) {
            int next = 0;
            int nextpos = 0;
            for (int j = 1; j <= n; j++) {
                if (A[j] == current)
                    continue;

                if (A[j] > m) {
                    next = 0;
                    nextpos = j;
                    break;
                } else {
                    if (cnt[A[j]] > target[A[j]]) {
                        next = A[j];
                        nextpos = j;
                        break;
                    }
                }
            }  // for

            cnt[current]++;
            cnt[next]--;
            A[nextpos] = current;
            answer2++;
        }  // while
    }      // for

    printf("%d %d\n", answer1, answer2);
    for (int i = 1; i <= n; i++) {
        printf("%d ", A[i]);
    }  // for

    return 0;
}  // function main
