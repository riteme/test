// FSX **

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 300000

struct Node {
    int tm, nxt, rt;
    bool read;
};

static int n, m, q;
static Node e[NMAX + 10];
static int head[NMAX + 10];

int main() {
    scanf("%d%d", &n, &q);
    int last = 0, cnt = 0;
    for (int i = 1; i <= q; i++) {
        int op, t;
        scanf("%d%d", &op, &t);
        if (op == 1) {
            m++; cnt++;
            e[m] = {m, 0, head[t], false};
            if (last) e[last].nxt = m;
            else head[0] = m;
            head[t] = last = m;
        } else if (op == 2) {
            for (int x = head[t]; x; x = e[x].rt) {
                cnt -= !e[x].read;
                e[x].read = true;
            }
            head[t] = 0;
        } else {
            for (int x = head[0]; x && e[x].tm <= t; x = e[x].nxt) {
                cnt -= !e[x].read;
                e[x].read = true;
                head[0] = e[x].nxt;
            }
            if (!head[0]) last = 0;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
