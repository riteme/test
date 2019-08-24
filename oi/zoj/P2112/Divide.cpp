#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 1000000
// #define NMAX 100

static int cnt;
static int a[NMAX];
static int num[NMAX];

enum CommandType {
    COMM_REMOVE = 1,
    COMM_ADD = 2,
    COMM_QUERY = 3
};  // enum CommandType

struct Command {
    CommandType type;
    int i, j, k;
    int current;
    int ansid;
};  // struct Command

static int n, q;
static int qcnt;
static Command ops[NMAX];
static Command *aux[NMAX];
static int sum[NMAX];
static Command *lq[NMAX], *rq[NMAX];
static int fenwick[NMAX];
static int querycnt;
static int answer[NMAX];

inline void modify(int x, int delta) {
    for (int i = x; i <= n; i += i & (-i))
        fenwick[i] += delta;
}

inline int query(int r) {
    int answer = 0;

    for (int i = r; i; i -= i & (-i))
        answer += fenwick[i];

    return answer;
}

static void solve(int head, int tail, int left, int right) {
    if (tail < head)
        return;
    if (left == right) {
        for (int i = head; i <= tail; i++) {
            if (aux[i]->type == COMM_QUERY)
                answer[aux[i]->ansid] = num[left];
        }

        return;
    }

    int mid = (left + right) >> 1;
    for (int i = head; i <= tail; i++) {
        Command *op = aux[i];

        if (op->type == COMM_REMOVE && op->j <= num[mid])
            modify(op->i, -1);
        else if (op->type == COMM_ADD && op->j <= num[mid])
            modify(op->i, 1);
        else if (op->type == COMM_QUERY)
            sum[i] = query(op->j) - query(op->i - 1);
    }  // for

    for (int i = head; i <= tail; i++) {
        Command *op = aux[i];

        if (op->type == COMM_REMOVE && op->j <= num[mid])
            modify(op->i, 1);
        else if (op->type == COMM_ADD && op->j <= num[mid])
            modify(op->i, -1);
    }  // for

    int ls = 0, rs = 0;
    for (int i = head; i <= tail; i++) {
        Command *op = aux[i];

        if (op->type == COMM_QUERY) {
            if (op->current + sum[i] >= op->k)
                lq[++ls] = op;
            else {
                rq[++rs] = op;
                op->current += sum[i];
            }
        } else {
            if (op->j <= num[mid])
                lq[++ls] = op;
            else
                rq[++rs] = op;
        }
    }  // for

    int pos = head;
    for (int i = 1; i <= ls; i++)
        aux[pos++] = lq[i];
    for (int i = 1; i <= rs; i++)
        aux[pos++] = rq[i];

    solve(head, head + ls - 1, left, mid);
    solve(head + ls, tail, mid + 1, right);
}

static void initialize() {
    scanf("%d%d", &n, &q);

    cnt = qcnt = querycnt = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);

        a[i] = x;
        num[++cnt] = x;
        ops[++qcnt].type = COMM_ADD;
        ops[qcnt].i = i;
        ops[qcnt].j = x;
    }  // for

    char buffer[10];
    for (int _cnt = 1; _cnt <= q; _cnt++) {
        scanf("%s", buffer);

        if (buffer[0] == 'Q') {
            ops[++qcnt].type = COMM_QUERY;
            ops[qcnt].current = 0;
            ops[qcnt].ansid = ++querycnt;
            scanf("%d%d%d", &ops[qcnt].i, &ops[qcnt].j, &ops[qcnt].k);
        } else {
            int i, j;
            scanf("%d%d", &i, &j);

            num[++cnt] = j;
            ops[++qcnt].type = COMM_REMOVE;
            ops[qcnt].i = i;
            ops[qcnt].j = a[i];
            ops[++qcnt].type = COMM_ADD;
            ops[qcnt].i = i;
            ops[qcnt].j = j;
            a[i] = j;
        }
    }  // for

    for (int i = 1; i <= qcnt; i++)
        aux[i] = ops + i;

    sort(num + 1, num + cnt + 1);
    cnt = unique(num + 1, num + cnt + 1) - num - 1;
}

int main() {
    freopen("dynrank.in", "r", stdin);
    freopen("dynrank.out", "w", stdout);

    int t;
    scanf("%d", &t);

    for (int _c = 0; _c < t; _c++) {
        initialize();
        solve(1, qcnt, 1, cnt);

        for (int i = 1; i <= querycnt; i++)
            printf("%d\n", answer[i]);
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
