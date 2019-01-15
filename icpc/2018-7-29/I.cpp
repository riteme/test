#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define INF 1000000000
#define ADD 101
#define SUB 102
#define MUL 103
#define DIV 104
#define TMAX 5
#define NMAX 7

struct Node {
    Node(int _lch, int _rch, int &_val)
        : lch(_lch), rch(_rch), val(_val) {}
    int lch, rch;
    int &val;
};

static int dat[NMAX], seq[NMAX];

struct ExpTree {
    int L[NMAX], R[NMAX];

    Node operator[](int i) {
        i--;
        return Node(L[i], R[i], dat[i]);
    }
};

static ExpTree Ts[TMAX] = {
    {{2, 3, 4}, {7, 6, 5}},
    {{2, 4, 5}, {7, 3, 6}},
    {{4, 5, 6}, {2, 3, 7}},
    {{4, 3, 5}, {2, 7, 6}},
    {{2, 4, 6}, {3, 5, 7}}
};

static ExpTree T;

int dp(Node x) {
    if (!x.lch) return x.val;
    int lv = dp(T[x.lch]), rv = dp(T[x.rch]);
    switch (x.val) {
        case ADD: x.val = lv + rv; break;
        case SUB: x.val = lv - rv; break;
        case MUL: x.val = lv * rv; break;
        case DIV: {
            if (rv && lv % rv == 0) x.val = lv / rv;
            else x.val = -INF;
        } break;
    }
    return x.val;
}

static int perm[NMAX];

int eval() {
    int cnt = 0;
    for (int i = 0; i <= 6; i++)
        dat[i] = seq[perm[i]];
    for (int i = 3; i < 6; i++) for (int j = i + 1; j <= 6; j++)
        if (perm[i] > perm[j]) cnt++;
    cnt *= 2;

    for (int i = 1; i <= 3; i++) {
        Node x = T[i];
        int lv = T[x.lch].val, rv = T[x.rch].val;
        if ((x.val == MUL || x.val == DIV) && (lv == ADD || lv == SUB))
            cnt++;
        if (x.rch < 4 && !((x.val == ADD || x.val == SUB) && (rv == MUL || rv == DIV)))
            cnt++;
    }

    int ans = dp(T[1]);
    for (int i = 1; i <= 7; i++)
        if (T[i].val == -INF) return -1;
    return ans == 24 ? cnt : -1;
}

int main() {
    scanf("%d%d%d%d", seq + 3, seq + 4, seq + 5, seq + 6);

    int val = INF;
    for (int i = 0; i < TMAX; i++) {
        T = Ts[i];
        for (seq[0] = ADD; seq[0] <= DIV; seq[0]++)
        for (seq[1] = ADD; seq[1] <= DIV; seq[1]++)
        for (seq[2] = ADD; seq[2] <= DIV; seq[2]++) {
            for (int i = 0; i <= 6; i++)
                perm[i] = i;
            do {
                int ret = eval();
                if (ret >= 0) val = min(val, ret);
            } while (next_permutation(perm + 3, perm + 7));
        }
    }

    if (val >= INF) puts("impossible");
    else printf("%d\n", val);

    return 0;
}
