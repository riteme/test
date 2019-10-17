#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define RT 0
#define DW 1

struct Node {
    Node() { memset(this, 0, sizeof(Node)); }

    int v;
    Node *p[2];
};

static int n, m, q;
static Node *head[NMAX + 10], *entry;
static Node *a[2][8][NMAX + 10];

void scan(int dir, int i1, int i2, int x1, int y1, int x2, int y2) {
    Node *u = entry;
    for (int i = 0; i < x1; i++) u = u->p[DW];
    for (int j = 0; j < y1; j++) u = u->p[RT];

    if (dir == DW) {
        for (int j = y1; j <= y2; j++, u = u->p[RT]) {
            a[DW][i1][j - y1] = u;
            a[DW][i2][j - y1] = u->p[DW];
        }
    } else {
        for (int i = x1; i <= x2; i++, u = u->p[DW]) {
            a[RT][i1][i - x1] = u;
            a[RT][i2][i - x1] = u->p[RT];
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i <= n + 1; i++) {
        Node *lp = nullptr;
        for (int j = 0; j <= m + 1; j++) {
            Node *x = new Node;
            if (!i && !j) entry = x;
            if (0 < i && i <= n && 0 < j && j <= m)
                scanf("%d", &x->v);
            if (head[j]) head[j]->p[DW] = x;
            head[j] = x;
            if (lp) lp->p[RT] = x;
            lp = x;
        }
    }

    while (q--) {
        int x1, y1, x2, y2, w, h;
        scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &h, &w);

        scan(RT, 0, 6, x1, y1 - 1, x1 + h - 1, y1 - 1);
        scan(RT, 1, 7, x1, y1 + w - 1, x1 + h - 1, y1 + w - 1);
        scan(RT, 2, 4, x2, y2 - 1, x2 + h - 1, y2 - 1);
        scan(RT, 3, 5, x2, y2 + w - 1, x2 + h - 1, y2 + w - 1);
        scan(DW, 0, 6, x1 - 1, y1, x1 - 1, y1 + w - 1);
        scan(DW, 1, 7, x1 + h - 1, y1, x1 + h - 1, y1 + w - 1);
        scan(DW, 2, 4, x2 - 1, y2, x2 - 1, y2 + w - 1);
        scan(DW, 3, 5, x2 + h - 1, y2, x2 + h - 1, y2 + w - 1);

        for (int k = 0; k < 4; k++) {
            for (int i = 0; i < h; i++)
                a[RT][k][i]->p[RT] = a[RT][k + 4][i];
            for (int j = 0; j < w; j++)
                a[DW][k][j]->p[DW] = a[DW][k + 4][j];
        }
    }

    for (Node *u = entry->p[DW]; u; u = u->p[DW]) {
        for (Node *v = u; v; v = v->p[RT])
            if (v->v) printf("%d ", v->v);
        puts("");
    }

    return 0;
}
