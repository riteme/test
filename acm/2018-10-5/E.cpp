#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define L 0
#define D 1
#define R 2
#define U 3

inline int rev(int d) {
    return (d + 2) & 3;
}

inline int dec(int d) {
    return (d - 1) & 3;
}

struct Node {
    char ch;
    int rt = 0;
    Node *dat[4] = {nullptr};

    Node *&at(int i) {
        return dat[(i + rt) & 3];
    }

    Node *&to(int i) {
        int p = (i + rt) & 3, q;
        Node *&r = dat[p];
        for (q = 0; q < 4 && r->dat[q] != this; q++) ;
        r->rt = (rt + q - p + 2) & 3;
        return r;
    }
};

static int n, q;
static char mat[NMAX + 10][NMAX + 10];
static Node *head;

Node *setup() {
    Node *ret, *last = nullptr;
    for (int i = 0; i <= n + 1; i++) {
        Node *row = new Node;
        if (!i) ret = row;
        Node *lp = row, *cp;
        for (int j = 1; j <= n + 1; j++) {
            cp = new Node;
            if (1 <= i && i <= n && 1 <= j && j <= n) cp->ch = mat[i][j];
            lp->dat[R] = cp;
            cp->dat[L] = lp;
            lp = cp;
        }
        if (last) {
            lp = last;
            cp = row;
            for (int i = 0; i <= n + 1; i++) {
                lp->dat[D] = cp;
                cp->dat[U] = lp;
                lp = lp->dat[R];
                cp = cp->dat[R];
            }
        }
        last = row;
    }
    return ret;
}

void rotate(int x, int y, int w) {
    static Node *in[4][NMAX + 10], *ex[4][NMAX + 10];
    Node *p = head;
    while (x--) p = p->at(D);
    while (y--) p = p->to(R);
    for (int d = 0; d < 4; d++) for (int i = 1, dn = (d + 1) & 3; i <= w; i++) {
        in[d][i] = p;
        ex[d][i] = p->to(d);
        p->at(d)->at(rev(d)) = nullptr;
        p->at(d) = nullptr;
        if (i < w) p = p->to(dn);
    }
    for (int d = 0; d < 4; d++) for (int i = 1, dn = (d - 1) & 3; i <= w; i++) {
        in[dn][i]->at(dec(d)) = ex[d][i];
        ex[d][i]->at(rev(d)) = in[dn][i];
    }
}

void print() {
    Node *line = head->at(D);
    for (int i = 1; i <= n; i++) {
        Node *col = line;
        for (int j = 1; j <= n; j++) {
            col = col->to(R);
            putchar(col->ch);
        }
        putchar('\n');
        line = line->at(D);
    }
}

void initialize() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%s", mat[i] + 1);
    head = setup();
}

int main() {
    initialize();
    while (q--) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        rotate(x, y, w);
    }
    print();
    return 0;
}
