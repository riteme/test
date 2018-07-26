#include <cstdio>
#include <cstring>
#include <climits>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, R, B, t;
static char S[NMAX + 10];
static int seq[NMAX + 10];

int main() {
    scanf("%d%d%d%s", &n, &R, &B, S + 1);
    t = n;
    deque<int> q;
    int rcnt = 0, bcnt = 0;
    for (int i = 1; i <= n; i++) {
        q.push_front(i);

        if (S[i] == 'R') rcnt++;
        else bcnt++;
        if (q.size() > R + B) {
            if (S[q[R + B]] == 'R') rcnt--;
            else bcnt--;
        }

        if (rcnt == R && bcnt == B) {
            for (int j = 0; j < R + B; j++) {
                seq[t--] = q[0];
                q.pop_front();
            }

            rcnt = bcnt = 0;
            for (int j = 0; j < R + B && j < q.size(); j++) {
                if (S[q[j]] == 'R') rcnt++;
                else bcnt++;
            }
        }
    }

    if (t) puts("NO");
    else {
        printf("YES\n%d\n", n / (R + B));
        for (int i = 1; i <= n; i += R + B) {
            for (int j = 0; j < R + B; j++)
                printf("%d ", seq[i + j]);
            putchar('\n');
        }
    }

    return 0;
}
