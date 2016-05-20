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
    for (; x <= n; x += x & (-x))
        s[x] += v;
}

#define OP_ADD 1
#define OP_QUERY 2

struct Operation {
    char type;
    int x, y, v;
    int timestamp;
    int id, flag;
    int prev, next;
};  // struct Operation

static int q, cnt;
static int answer[QMAX + 10];
static Operation op[QMAX + 10];
static int add_cnt;
static Operation *add[QMAX + 10];
static int que_cnt;
static Operation *que[QMAX + 10];
static int before[QMAX + 10];

static int first = 1;
inline void pop(int x) {
    if (x == first) {
        first = add[x]->next;
    }

    add[add[x]->prev]->next = add[x]->next;
}

inline void add_operation(char type, int x, int y, int v = 0, int id = 0,
                          int flag = 0) {
    cnt++;
    Operation &p = op[cnt];
    p.type = type;
    p.x = x;
    p.y = y;
    p.v = v;
    p.timestamp = cnt;
    p.id = id;
    p.flag = flag;

    if (type == OP_ADD) {
        add_cnt++;
        add[add_cnt] = &p;
    } else {
        que_cnt++;
        que[que_cnt] = &p;
    }
}

static bool compare(const Operation *x, const Operation *y) {
    return x->x < y->x && (x->x == y->x && x->timestamp < y->timestamp);
}

static void read_operations() {
    int command;
    scanf("%d%d", &command, &n);

    cnt = 0;
    bool flag = true;
    while (flag) {
        scanf("%d", &command);

        switch (command) {
            case 1: {
                int x, y, v;
                scanf("%d%d%d", &x, &y, &v);
                // x++, y++;

                add_operation(OP_ADD, x, y, v);
            } break;

            case 2: {
                q++;
                int x1, y1, x2, y2;
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                // x1++, x2++, y1++, y2++;

                add_operation(OP_QUERY, x1 - 1, y1 - 1, 0, q, 1);
                add_operation(OP_QUERY, x1 - 1, y2, 0, q, -1);
                add_operation(OP_QUERY, x2, y1 - 1, 0, q, -1);
                add_operation(OP_QUERY, x2, y2, 0, q, 1);
            } break;
            default: flag = false; break;
        }  // switch to command
    }      // while

    for (int i = 1; i <= cnt; i++) {
        before[i] = before[i - 1] + (op[i].type == OP_ADD ? 1 : 0);
    }  // for

    sort(add + 1, add + add_cnt + 1, compare);
    sort(que + 1, que + que_cnt + 1, compare);

    add[0] = new Operation;
    for (int i = 1; i < add_cnt; i++) {
        add[i]->next = i + 1;
        add[i]->prev = i - 1;
    }  // for

    for (int i = 1; i < que_cnt; i++) {
        que[i]->next = i + 1;
        que[i]->prev = i - 1;
    }  // for
}

static int processed;
static void solve() {
    for (int i = 1; i <= que_cnt; i++) {
        Operation *target = que[i];

        for (int j = first;
             j <= add_cnt && processed < before[que[i]->timestamp] &&
                 add[j]->x <= que[i]->x;
             j++) {
            Operation *a = add[j];

            if (a->timestamp < target->timestamp) {
                modify(a->y, a->v);
                processed++;
                pop(j);
            }
        }  // for

        target->v = query(target->y);
        // printf("(%d, %d) += %d\n", target->x, target->y, target->v);
    }  // for
}

int main() {
    // freopen("mokia.in", "r", stdin);
    // freopen("mokia.out", "w", stdout);
    read_operations();
    solve();

    for (int i = 1; i <= que_cnt; i++) {
        Operation *p = que[i];

        if (p->type == OP_QUERY)
            answer[p->id] += p->v * p->flag;
    }  // for

    for (int i = 1; i <= q; i++)
        printf("%d\n", answer[i]);

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
