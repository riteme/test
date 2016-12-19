#include <cstdio>
#include <climits>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define INFTY 1000000000

struct Node {
    Node (int _left, int _right)
        : left(_left), right(_right),
          answer(0), minv(INFTY), maxv(-INFTY),
          leftchild(nullptr), rightchild(nullptr) {}

    int left;
    int right;
    int answer;
    int minv;
    int maxv;
    int mark;
    Node *leftchild;
    Node *rightchild;

    inline int maxvalue() const {
        return maxv + mark;
    }

    inline int minvalue() const {
        return minv + mark;
    }

    void pushdown() {
        if (mark) {
            maxv += mark;
            minv += mark;

            if (left < right) {
                leftchild->mark += mark;
                rightchild->mark += mark;
            }

            mark = 0;
        }
    }

    void update() {
        if (left < right) {
            maxv = max(
                leftchild->maxvalue(),
                rightchild->maxvalue()
            );

            minv = min(
                leftchild->minvalue(),
                rightchild->minvalue()
            );

            answer = max(
                leftchild->maxvalue() - rightchild->minvalue(),
                max(leftchild->answer,
                    rightchild->answer)
            );
        }
    }
};

static Node *build(int left, int right, int *seq) {
    Node *x = new Node(left, right);

    if (left < right) {
        int mid = (left + right) / 2;
        x->leftchild = build(left, mid, seq);
        x->rightchild = build(mid + 1, right, seq);
        x->update();
    } else {
        x->maxv = x->minv = seq[left];
    }

    return x;
}

static void modify(Node *x, int pos, int v) {
    if (x->left == x->right)
        x->maxv = x->minv = v;
    else {
        int mid = (x->left + x->right) / 2;

        x->pushdown();

        if (pos <= mid)
            modify(x->leftchild, pos, v);
        else
            modify(x->rightchild, pos, v);

        x->update();
    }
}

static void modify(Node *x, int left, int right, int v) {
    if (left <= x->left && x->right <= right)
        x->mark += v;
    else {
        int mid = (x->left + x->right) / 2;

        x->pushdown();

        if (right <= mid)
            modify(x->leftchild, left, right, v);
        else if (left > mid)
            modify(x->rightchild, left, right, v);
        else {
            modify(x->leftchild, left, right, v);
            modify(x->rightchild, left, right, v);
        }

        x->update();
    }
}

struct Result {
    Result()
        : answer(0), max(0), min(0) {}
    Result(int _answer, int _max, int _min)
        : answer(_answer), max(_max), min(_min) {}

    int answer;
    int max;
    int min;
};

static Result query(Node *x, int left, int right) {
    if (left <= x->left && x->right <= right)
        return Result(x->answer, x->maxvalue(), x->minvalue());
    else if (x->right < left || x->left > right)
        return Result(0, -INFTY, INFTY);
    else {
        x->pushdown();

        Result l = query(x->leftchild, left, right);
        Result r = query(x->rightchild, left, right);

        return Result(
            max(max(l.answer, r.answer), l.max - r.min),
            max(l.max, r.max),
            min(l.min, r.min)
        );
    }
}

static int n, q;
static int seq[NMAX * 2 + 10];
static Node *tree; 

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
    }

    for (int i = n + 1; i <= n + q; i++) {
        seq[i] = INFTY;
    }

    scanf("%d", &q);

    tree = build(1, n + q, seq);
}

int main() {
    initialize();

    char command[10];
    int tail = n + 1;
    while (q--) {
        scanf("%s", command);

        if (command[0] == 'M') {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);

            modify(tree, l, r, x);
        } else {
            int l, r;
            scanf("%d%d", &l, &r);

            int m = query(tree, l, r).answer;
            printf("%d\n", m);

            if (m > 0)
                modify(tree, tail++, m);
        }
    }

    return 0;
}

