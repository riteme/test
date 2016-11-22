/**
 * 思路不清晰者挂得惨
 * 1. 首先是考虑各种左边界，要取一个最小值
 * 2. 记录的maxlen需要考虑到自己的儿子（考虑分治的过程）
 */

#include <cstdio>
#include <climits>
#include <cstring>

#include <algorithm>

using namespace std;

#define TO_WHITE 1
#define TO_BLACK 2

struct Node {
    Node(int _left, int _right)
        : left(_left), right(_right),
          maxlen( {1, 1, 1, 0} ),
          mark(0), leftchild(NULL), rightchild(NULL) {}

    int left;
    int right;
    struct {
        int left;
        int right;
        int center;
        int cmax;
    } maxlen;
    int mark;
    Node *leftchild;
    Node *rightchild;

    int length() const {
        return right - left + 1;
    }

    int left_maxlen() const {
        if (mark == TO_WHITE)
            return length();
        else if (mark == TO_BLACK)
            return 0;
        return maxlen.left;
    }

    int right_maxlen() const {
        if (mark == TO_WHITE)
            return length();
        else if (mark == TO_BLACK)
            return 0;
        return maxlen.right;
    }

    int center_maxlen() const {
        if (mark == TO_WHITE)
            return length();
        else if (mark == TO_BLACK)
            return 0;
        return maxlen.center;
    }

    int child_maxlen() const {
        if (mark == TO_WHITE)
            return length();
        else if (mark == TO_BLACK)
            return 0;
        return maxlen.cmax;
    }

    int max_len() const {
        return max(max(left_maxlen(), right_maxlen()),
                   max(center_maxlen(), child_maxlen()));
    }

    bool empty() const {
        return mark == TO_WHITE || center_maxlen() == length();
    }
};

inline void update(Node *x) {
    if (x->left == x->right)
        return;

    if (x->leftchild->empty())
        x->maxlen.left =
            x->leftchild->length() + x->rightchild->left_maxlen();
    else
        x->maxlen.left =
            x->leftchild->left_maxlen();

    if (x->rightchild->empty())
        x->maxlen.right =
            x->rightchild->length() + x->leftchild->right_maxlen();
    else
        x->maxlen.right =
            x->rightchild->right_maxlen();

    x->maxlen.center =
        x->leftchild->right_maxlen() + x->rightchild->left_maxlen();
    x->maxlen.cmax = max(
        x->leftchild->max_len(),
        x->rightchild->max_len()
    );
}

inline void pushdown(Node *x) {
    if (x->mark == TO_WHITE)
        x->maxlen.left = x->maxlen.right =
        x->maxlen.center = x->maxlen.cmax = x->length();
    else if (x->mark == TO_BLACK)
        x->maxlen.left = x->maxlen.right =
        x->maxlen.center = x->maxlen.cmax = 0;

    if (x->mark && x->left < x->right) {
        x->leftchild->mark = x->mark;
        x->rightchild->mark = x->mark;
    }

    x->mark = 0;
}

static Node *build(int left, int right) {
    Node *x = new Node(left, right);

    if (left < right) {
        int mid = (left + right) / 2;
        x->leftchild = build(left, mid);
        x->rightchild = build(mid + 1, right);
        update(x);
    }

    return x;
}

static void modify(Node *x, int left, int right, int type) {
    if (left <= x->left && x->right <= right)
        x->mark = type;
    else {
        pushdown(x);

        int mid = (x->left + x->right) / 2;
        if (right <= mid)
            modify(x->leftchild, left, right, type);
        else if (left > mid)
            modify(x->rightchild, left, right, type);
        else {
            modify(x->leftchild, left, right, type);
            modify(x->rightchild, left, right, type);
        }

        update(x);
    }
}

static int find_leftist(Node *x, int limit) {
    if (x->left == x->right) {
        if (x->empty() && limit == 1)
            return x->left;
        return INT_MAX;
    }
    
    pushdown(x);

    int pos = INT_MAX;
    if (x->maxlen.left >= limit)
        pos = x->left;
    if (x->maxlen.center >= limit)
        pos = min(
                pos,
                x->leftchild->right - x->leftchild->right_maxlen() + 1
            );
    if (x->maxlen.right >= limit)
        pos = min(
                pos,
                x->right - x->maxlen.right + 1
            );

    if (x->leftchild->max_len() >= limit)
        return min(pos, find_leftist(x->leftchild, limit));
    else if (x->rightchild->max_len() >= limit)
        return min(pos, find_leftist(x->rightchild, limit));

    return pos;
}

#define CHECKIN 1
#define CHECKOUT 2

int main() {
    // freopen("hotel.in", "r", stdin);

    int n, m;
    scanf("%d%d", &n, &m);

    Node *tree = build(1, n);
    while (m--) {
        int type;
        scanf("%d", &type);

        if (type == CHECKIN) {
            int d;
            scanf("%d", &d);

            int pos = find_leftist(tree, d);

            if (pos < INT_MAX) {
                printf("%d\n", pos);

                modify(tree, pos, pos + d - 1, TO_BLACK);
            } else
                puts("0");
        } else if (type == CHECKOUT) {
            int x, d;
            scanf("%d%d", &x, &d);

            modify(tree, x, x + d - 1, TO_WHITE);
        }
    }
}
