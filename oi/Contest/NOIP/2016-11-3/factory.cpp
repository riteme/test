#pragma GCC optimize(3)

#include <cstdio>

#include <set>
#include <algorithm>

using namespace std;

#define NMAX 100000

inline int gcd(int a, int b) {
    while (b) {
        int tmp = a;
        a = b;
        b = tmp % b;
    }

    return a;
}

static int n;
static int seq[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
    }
}

int main() {
    freopen("factory.in", "r", stdin);
    freopen("factory.out", "w", stdout);
    initialize();

    int answer = 0;
    int d = 0;
    set<int> S;
    for (int i = 1; i <= n; i++) {
        if (S.empty()) {
            answer++;
            S.insert(seq[i]);
        } else if (S.size() == 1) {
            d = abs(seq[i] - *S.begin());

            if (d <= 1) {
                S.clear();
                answer++;
            }

            S.insert(seq[i]);
        } else {
            set<int>::iterator iter = S.upper_bound(seq[i]);

            int d1, d2 = -1;
            if (iter == S.begin())
                d1 = *S.begin() - seq[i];
            else if (iter == S.end())
                d1 = seq[i] - *S.rbegin();
            else {
                set<int>::iterator pre = iter;
                pre--;
                d1 = seq[i] - *pre;
                d2 = *iter - seq[i];
            }

            bool reset = false;
            if (d1 == 0)
                reset = true;
            else {
                d = gcd(d, d1);

                if (d <= 1)
                    reset = true;
            }

            if (d2 >= 0) {
                if (d2 == 0)
                    reset = true;
                else {
                    d = gcd(d, d2);

                    if (d <= 1)
                        reset = true;
                }
            }

            if (reset) {
                answer++;

                // for (set<int>::iterator beg = S.begin(); beg != S.end(); beg++) {
                //     printf("%d ", *beg);
                // }
                // printf("\n");

                S.clear();
            }

            S.insert(seq[i]);
        }
    }

    printf("%d\n", answer);

    return 0;
}
