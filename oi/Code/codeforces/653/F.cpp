#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 500000

typedef long long int64;

struct Segment {
    Segment(int l, int r)
        : left(l),
          right(r),
          value(0),
          leftchild(nullptr),
          rightchild(nullptr) {}

    int left;
    int right;
    int value;
    Segment *leftchild;
    Segment *rightchild;
};  // struct Segment

static Segment *build(int left, int right, int *arr) {
    Segment *x = new Segment(left, right);

    if (left < right) {
        int mid = (left + right) / 2;
        x->leftchild = build(left, mid, arr);
        x->rightchild = build(mid + 1, right, arr);

        if (arr)
            x->value = min(x->leftchild->value, x->rightchild->value);
    } else {
        if (arr)
            x->value = arr[left];
    }

    return x;
}

static int query_min(Segment *x, int left, int right) {
    if (left <= x->left && x->right <= right)
        return x->value;
    else {
        int mid = (x->left + x->right) / 2;
        int answer = INT_MAX;

        if (left <= mid)
            answer = min(answer, query_min(x->leftchild, left, right));
        if (right > mid)
            answer = min(answer, query_min(x->rightchild, left, right));

        return answer;
    }
}

static int find_first(Segment *x, int left, int right, int std) {
    if (x->left == x->right)
        return x->left;
    else {
        int mid = (x->left + x->right) / 2;

        if (query_min(x->leftchild, left, mid) < std)
            return find_first(x->leftchild, left, right, std);
        else
            return find_first(x->rightchild, left, right, std);
    }
}

static Segment *persistent_modify(Segment *x, int pos, int delta) {
    x = new Segment(*x);

    if (x->left == x->right) {
        x->value += delta;
    } else {
        int mid = (x->left + x->right) / 2;

        if (pos <= mid)
            x->leftchild = persistent_modify(x->leftchild, pos, delta);
        else
            x->rightchild = persistent_modify(x->rightchild, pos, delta);
    }

    return x;
}

static int query(Segment *x, int pos) {
    if (x->left == x->right)
        return x->value;
    else {
        int mid = (x->left + x->right) / 2;

        if (pos <= mid)
            return query(x->leftchild, pos);
        else
            return query(x->rightchild, pos);
    }
}

#define SIGMA 3
#define EOFCHAR 2

struct Node {
    struct Edge {
        Edge(int l, int r, Node *nxt) : left(l), right(r), next(nxt) {}

        int left;
        int right;
        Node *next;
    };  // struct Edge

    Node() : suffix_link(nullptr) {
        memset(trans, 0, sizeof(trans));
    }

    Node *suffix_link;
    Edge *trans[SIGMA];
};  // struct Node

typedef Node::Edge Edge;

static int n;
static int size;
static char str[NMAX + 10];

inline int length(const Edge *e) {
    return e->right ? e->right - e->left + 1 : size - e->left + 1;
}

static void append(Node *root, char c) {
    static Node *active = root;
    static char dir = -1;
    static int len = 0, cnt = 0;

    cnt++;
    Node *last = nullptr;
    while (cnt) {
        if (cnt - 1 < len) {
            len = cnt - 1;
            dir = len ? str[size - len + 1] : -1;
        }

        while (dir >= 0 && len >= length(active->trans[dir])) {
            len -= length(active->trans[dir]);
            active = active->trans[dir]->next;
            dir = len ? str[size - len + 1] : -1;
        }  // while

        if ((dir < 0 && active->trans[c]) ||
            (dir >= 0 && c == str[active->trans[dir]->left + len])) {
            if (dir < 0)
                dir = c;

            len++;

            if (last)
                last->suffix_link = active;

            break;
        }

        Node *x;
        if (dir < 0) {
            active->trans[c] = new Edge(size + 1, 0, new Node);
            x = active;
        } else {
            Edge *t = active->trans[dir];
            x = new Node;
            x->trans[c] = new Edge(size + 1, 0, new Node);
            x->trans[str[t->left + len]] =
                new Edge(t->left + len, t->right, t->next);
            t->right = t->left + len - 1;
            t->next = x;
        }

        if (last)
            last->suffix_link = x;
        last = x;

        active = active->suffix_link ? active->suffix_link : root;
        cnt--;
    }  // while

    size++;
}

static void fix(Node *x) {
    for (char c = 0; c < SIGMA; c++) {
        Edge *t = x->trans[c];

        if (t) {
            if (!t->right)
                t->right = size;

            fix(t->next);
        }
    }  // for
}

inline int code(char c) {
    if (c == '(')
        return 1;
    return -1;
}

static int pre[NMAX + 10];
static Segment *seg;
static Segment *version[NMAX + 10];

static int64 dfs(Node *x, int sum = 0) {
    int64 answer = 0;

    for (char c = 0; c < SIGMA; c++) {
        Edge *t = x->trans[c];

        if (!t)
            continue;

        int delta = pre[t->left - 1];
        if (sum + query_min(seg, t->left, t->right) - delta >= 0) {
            answer += query(version[t->right], n - sum + delta);
            answer -= query(version[t->left - 1], n - sum + delta);
        } else {
            int p = find_first(seg, t->left, t->right, delta - sum);
            answer += query(version[p - 1], n - sum + delta);
            answer -= query(version[t->left - 1], n - sum + delta);

            continue;
        }

        answer += dfs(t->next, sum + pre[t->right] - pre[t->left - 1]);
    }  // for

    return answer;
}

int main() {
    scanf("%d%s", &n, str + 1);

    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + code(str[i]);
    }  // for
    pre[n + 1] = n * 2 + 1;

    seg = build(1, n + 1, pre);

    version[0] = build(0, n * 2 + 1, nullptr);
    for (int i = 1; i <= n + 1; i++) {
        version[i] = persistent_modify(version[i - 1], pre[i] + n, 1);
    }  // for

    Node *tree = new Node;
    for (int i = 1; i <= n; i++) {
        str[i] -= '(';
        append(tree, str[i]);
    }  // for
    append(tree, EOFCHAR);
    fix(tree);

    printf("%lld\n", dfs(tree));

    return 0;
}  // function main
