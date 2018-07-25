#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define CMAX 1000000

struct Node {
    Node(int _left, int _right)
            : left(_left)
            , right(_right)
            , maxvalue(0)
            , minvalue(0)
            , leftchild(NULL)
            , rightchild(NULL) {}

    int left;
    int right;
    int maxvalue;
    int minvalue;
    Node *leftchild;
    Node *rightchild;
};  // struct Node

static int n;
static int h[NMAX + 10];
static int answer[NMAX + 10];
static Node *tree;

static Node *build(int left, int right) {
    Node *x = new Node(left, right);

    if (left == right) {
        x->maxvalue = x->minvalue = h[left];

        return x;
    }

    int mid = (left + right) / 2;
    x->leftchild = build(left, mid);
    x->rightchild = build(mid + 1, right);
    x->maxvalue = max(x->leftchild->maxvalue, x->rightchild->maxvalue);
    x->minvalue = min(x->leftchild->minvalue, x->rightchild->minvalue);
    return x;
}

static int query_max(Node *x, int left, int right) {
    if (left <= x->left && x->right <= right)
        return x->maxvalue;

    int mid = (x->left + x->right) / 2;
    if (right <= mid)
        return query_max(x->leftchild, left, right);
    else if (left > mid)
        return query_max(x->rightchild, left, right);
    else
        return max(query_max(x->leftchild, left, right),
                   query_max(x->rightchild, left, right));
}

static int query_min(Node *x, int left, int right) {
    if (left <= x->left && x->right <= right)
        return x->minvalue;

    int mid = (x->left + x->right) / 2;
    if (right <= mid)
        return query_min(x->leftchild, left, right);
    else if (left > mid)
        return query_min(x->rightchild, left, right);
    else
        return min(query_min(x->leftchild, left, right),
                   query_min(x->rightchild, left, right));
}

static int query(int limit) {
    int i = 1, j = 1;
    int answer = 0;
    while (i <= n) {
        if (j == n)
            break;

        while (j < n &&
               query_max(tree, i, j + 1) - query_min(tree, i, j + 1) <= limit)
            j++;

        answer = max(answer, j - i + 1);
        i++;
    }  // while

    return answer;
}

static int queue[NMAX + 10];
static int lqueue[NMAX + 10];
static int rqueue[NMAX + 10];

static void solve(int left, int right, int head, int tail) {
    if (tail < head)
        return;

    if ((double)right * 0.96 <= (double)left) {
        for (int i = head; i <= tail; i++)
            answer[queue[i]] = left;

        return;
    }

    int mid = (left + right) / 2;
    int length = query(mid);
    int lpos = 0, rpos = 0;
    for (int i = head; i <= tail; i++) {
        int p = queue[i];

        if (p <= length)
            lqueue[++lpos] = p;
        else
            rqueue[++rpos] = p;
    }  // for

    int pos = head;
    for (int i = 1; i <= lpos; i++)
        queue[pos++] = lqueue[i];
    for (int i = 1; i <= rpos; i++)
        queue[pos++] = rqueue[i];

    solve(left, mid, head, head + lpos - 1);
    solve(mid + 1, right, head + lpos, tail);
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", h + i);

    tree = build(1, n);
}

int main() {
    initialize();

    for (int i = 2; i <= n; i++)
        queue[i] = i;

    solve(1, CMAX, 2, n);

    for (int i = 2; i <= n; i++)
        printf("%d\n", answer[i]);

    return 0;
}  // function main
