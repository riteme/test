/**
 * Mokia
 * CDQ分治
 * 利用容斥原理，一次矩形的查询可以变为四个点查询（即四个顶点），用于查询二维前缀和
 * 这样点对点的贡献就很好计算了，直接按x排序后套在归并排序，每次递归就扫描一遍。
 * 为了能快速计算和更新前缀和，我们使用树状数组
 * 对于每个节点，只有O(1)次的操作，每次操作O(log n)
 * 因此总时间复杂度为O(m * log m * log n)
 *
 * 注意memset，不会是O(1)的，其运行时间与数组长度有关
 * 因此树状数组的清零只能通过修改操作
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 2000000
#define QMAX 1000000

static int n;
static int s[NMAX + 10];

inline int query(int r) {
    int answer = 0;
    for (; r > 0; r -= r & (-r))
        answer += s[r];
    return answer;
}

inline void modify(int x, int v) {
    // if (x == 0)
    //     return;
    for (; x <= n; x += x & (-x))
        s[x] += v;
}

#define OP_ADD 1
#define OP_QUERY 2

struct Operation {
    char type;
    int x, y, v;
    int id, flag;
};  // struct Operation

static int q, cnt;
static int answer[QMAX + 10];
static Operation op[QMAX + 10];
static Operation *a[QMAX + 10];
static Operation *aux[QMAX + 10];

inline void add_operation(char type, int x, int y, int v = 0, int id = 0,
                          int flag = 0) {
    cnt++;
    Operation &p = op[cnt];
    p.type = type;
    p.x = x;
    p.y = y;
    p.v = v;
    p.id = id;
    p.flag = flag;
    a[cnt] = &p;
}

static void read_operations() {
    int command;
    scanf("%d%d", &command, &n);

    cnt = 0;
    while (true) {
        scanf("%d", &command);

        switch (command) {
            case 1: {
                int x, y, v;
                scanf("%d%d%d", &x, &y, &v);

                add_operation(OP_ADD, x, y, v);
            } break;

            case 2: {
                q++;
                int x1, y1, x2, y2;
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

                add_operation(OP_QUERY, x1 - 1, y1 - 1, 0, q, 1);
                add_operation(OP_QUERY, x1 - 1, y2, 0, q, -1);
                add_operation(OP_QUERY, x2, y1 - 1, 0, q, -1);
                add_operation(OP_QUERY, x2, y2, 0, q, 1);
            } break;
            default: return;
        }  // switch to command
    }      // while
}

static bool compare(const Operation *x, const Operation *y) {
    return x->x < y->x;
}

static void solve(int left, int right) {
    if (left == right)
        return;

    int mid = (left + right) / 2;
    solve(left, mid);
    solve(mid + 1, right);

    for (int i = left; i <= right; i++) {
        aux[i] = a[i];
    }  // for

    // memset(s, 0, sizeof(s));  // 233
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (aux[i]->type != OP_ADD)
            i++;
        else if (aux[j]->type != OP_QUERY)
            j++;
        else if (aux[i]->x > aux[j]->x) {
            aux[j]->v += query(aux[j]->y);
            j++;
        } else {
            modify(aux[i]->y, aux[i]->v);
            i++;
        }
    }  // while

    for (; j <= right; j++) {
        if (aux[j]->type == OP_QUERY) {
            aux[j]->v += query(aux[j]->y);
        }
    }  // for

    for (int k = left; k < i; k++) {
        if (aux[k]->type == OP_ADD)
            modify(aux[k]->y, -aux[k]->v);
    }  // for

    i = left, j = mid + 1;
    int k = left;
    while (k <= right) {
        if (i > mid)
            a[k++] = aux[j++];
        else if (j > right)
            a[k++] = aux[i++];
        else if (compare(aux[i], aux[j]))
            a[k++] = aux[i++];
        else
            a[k++] = aux[j++];
    }  // while
}

int main() {
    freopen("mokia.in", "r", stdin);
    freopen("mokia.out", "w", stdout);
    read_operations();
    solve(1, cnt);

    for (int i = 1; i <= cnt; i++) {
        Operation &p = op[i];

        if (p.type == OP_QUERY)
            answer[p.id] += p.v * p.flag;
    }  // for

    for (int i = 1; i <= q; i++)
        printf("%d\n", answer[i]);

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
