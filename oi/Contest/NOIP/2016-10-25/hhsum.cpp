#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000

struct Node {
    Node ()
        : left(0), right(0), sum(0),
          leftchild(NULL), rightchild(NULL) {}
    Node(int _left, int _right)
        : left(_left), right(_right), sum(0),
          leftchild(NULL), rightchild(NULL) {}

    int left;
    int right;
    int sum;
    Node *leftchild;
    Node *rightchild;
};

inline void update(Node *x) {
    if (x->leftchild)
        x->sum = x->leftchild->sum + x->rightchild->sum;
}

static Node *build(int left, int right) {
    Node *x = new Node(left, right);

    if (left != right) {
        int mid = (left + right) / 2;
        x->leftchild = build(left, mid);
        x->rightchild = build(mid + 1, right);
    }

    return x;
}

static Node *persistent_modify(Node *x, int pos, int v) {
    Node *y = new Node;
    *y = *x;
    x = y;

    if (x->left == x->right)
        x->sum += v;
    else {
        int mid = (x->left + x->right) / 2;

        if (pos <= mid)
            x->leftchild = persistent_modify(x->leftchild, pos, v);
        else
            x->rightchild = persistent_modify(x->rightchild, pos, v);
    }

    update(x);
    return x;
}

static int query(Node *x, int left, int right) {
    if (left <= x->left &&  x->right <= right)
        return x->sum;

    int mid = (x->left + x->right) / 2;
    if (right <= mid)
        return query(x->leftchild, left, right);
    else if (left > mid)
        return query(x->rightchild, left, right);
    else
        return query(x->leftchild, left, right) + query(x->rightchild, left, right);
}

static int n, q;
static int seq[NMAX + 10];
static int id[NMAX + 10];
static int vcnt;
static int sorted[NMAX + 10];
static Node *version[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    version[0] = build(1, n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
        sorted[++vcnt] = seq[i];
    }

    sort(sorted + 1, sorted + vcnt + 1);
    vcnt = unique(sorted + 1, sorted + vcnt + 1) - sorted - 1;
    sorted[0] = 0;
    sorted[++vcnt] = INT_MAX;

    version[0] = build(0, vcnt);
    for (int i = 1; i <= n; i++) {
        id[i] = lower_bound(sorted + 1, sorted + vcnt + 1, seq[i]) - sorted;
        version[i] = persistent_modify(version[i - 1], id[i], seq[i]);
    }
}

static int get(int left, int right) {
    int answer = 1;
    
    while (true) {
        int ansid = upper_bound(sorted, sorted + vcnt + 1, answer) - sorted - 1;
        int sum = query(version[right], 0, ansid) - query(version[left - 1], 0, ansid);

        if (sum >= answer)
            answer = sum + 1;
        else
            break;
    }

    return answer;
}

int main() {
    freopen("hhsum.in", "r", stdin);
    freopen("hhsum.out", "w", stdout);
    initialize();

    scanf("%d", &q);
    while (q--) {
        int left, right;
        scanf("%d%d", &left, &right);
        
        printf("%d\n", get(left, right));
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
