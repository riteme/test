#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define QMAX 10000

#define OP_ADD 1
#define OP_QUERY 2

struct Operation {
    int type;
    int a;
    int b;
    int result;
};  // struct Operation

static int n, q;
static int sum[NMAX + 10];
static Operation op[QMAX + 10];
static Operation *a[QMAX + 10];
static Operation *s[QMAX + 10];

static void initialize() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", sum + i);
        sum[i] += sum[i - 1];
    }  // for

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d", &op[i].type);
        scanf("%d%d", &op[i].a, &op[i].b);

        a[i] = &op[i];
    }  // for
}

static void solve(int left, int right) {
    if (right <= left)
        return;

    int mid = (left + right) / 2;
    solve(left, mid);
    solve(mid + 1, right);

    for (int i = left; i <= right; i++) {
        s[i] = a[i];
    }  // for

    int i = left;
    int j = mid + 1;
    while ((j <= right) && (i <= mid && s[i]->type != OP_QUERY)) {
        Operation *x = s[i];
        Operation *y = s[j];

        if (y->type == OP_ADD) {
            j++;
        } else {  // Contribution
            int k = j;
            while (k <= right) {
                if (s[k]->a <= x->a && x->a <= s[k]->b) {
                    s[k]->result += x->b;
                }
                k++;
            }  // while
            i++;
        }
    }  // while

    i = left;
    j = mid + 1;
    int k = left;
    while (k <= right) {
        if (i > mid)
            a[k++] = s[j++];
        else if (j > right)
            a[k++] = s[i++];
        else if (s[i]->type < s[j]->type)
            a[k++] = s[i++];
        else
            a[k++] = s[j++];
    }  // while
}

int main() {
    initialize();

    solve(1, q);
    for (int i = 1; i <= q; i++) {
        if (op[i].type == OP_QUERY) {
            printf("%d\n", op[i].result + sum[op[i].b] - sum[op[i].a - 1]);
        }
    }  // for

    return 0;
}  // function main
