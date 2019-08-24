#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 10000000

#define OP_ADD 1
#define OP_QUERY 2
#define OP_UNKNOWN 0

struct Opeartion {
    int type;
    int x, y;
    int result;
};  // struct Opeartion

static int n;
static Opeartion op[NMAX + 10];
static Opeartion *a[NMAX + 10];
static Opeartion *aux[NMAX + 10];

static void read_operations() {
    char buffer[10];
    int x;
    n = 0;
    while (scanf("%s%d", buffer, &x) != EOF) {
        n++;
        if (buffer[0] == 'A') {
            op[n].type = OP_ADD;
            scanf("%d", &op[n].y);
        } else if (buffer[0] == 'Q') {
            op[n].type = OP_QUERY;
        } else {
            op[n].type = OP_UNKNOWN;
        }

        op[n].x = x;
        a[n] = &op[n];
    }  // for
}

static void initialize() {
    read_operations();
}

static void process(int left, int right) {
    if (left == right)
        return;

    int mid = (left + right) / 2;
    process(left, mid);
    process(mid + 1, right);

    for (int i = left; i <= right; i++) {
        aux[i] = a[i];
    }  // for

    int i = left;
    int j = mid + 1;
    while (i <= mid && j <= right) {
        if (aux[j]->type != OP_QUERY)
            j++;
        else if (aux[i]->type != OP_ADD)
            i++;
        else if (aux[i]->x < aux[j]->x)
            i++;
        else if (aux[i]->x > aux[j]->x)
            j++;
        else if (aux[j]->result == 0) {
            aux[j]->result = aux[i]->y;
            j++;
        } else
            j++;
    }  // while

    i = left;
    j = mid + 1;
    int k = left;
    while (k <= right) {
        if (i > mid)
            a[k++] = aux[j++];
        else if (j > right)
            a[k++] = aux[i++];
        else if (aux[i]->type < aux[j]->type)
            a[k++] = aux[i++];
        else if (aux[i]->type > aux[j]->type)
            a[k++] = aux[j++];
        else if (aux[i]->x < aux[j]->x)
            a[k++] = aux[i++];
        else
            a[k++] = aux[j++];
    }  // while
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    initialize();
    process(1, n);

    for (int i = 1; i <= n; i++) {
        if (op[i].type == OP_QUERY) {
            printf("%d\n", op[i].result);
        }
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
