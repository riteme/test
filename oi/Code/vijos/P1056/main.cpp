#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

#define NMAX 1000

#define EVENTTYPE_ENTER 1
#define EVENTTYPE_EXIT 2

struct EventPoint {
    int y;
    int left, right;
    char type;

    bool operator<(const EventPoint &p) const {
        return y < p.y;
    }
};  // struct EventPoint

#define NONE_MARK 0
#define FILLED_MARK 1
#define CLEANED_MARK 2

struct Node {
    Node() : value(0), covered_width(0), leftchild(NULL), rightchild(NULL) {}

    int left, right;
    int value;
    int covered_width;

    Node *leftchild, *rightchild;
};  // struct Node

static int n;
static int x1[NMAX + 10];
static int x2[NMAX + 10];
static int y1[NMAX + 10];
static int y2[NMAX + 10];
static int pos;
static int cnt;
static int xs[NMAX * 2 + 10];
static int width[NMAX * 2 + 10];
static EventPoint events[NMAX * 2 + 10];
static Node *tree;

inline void update(Node *x) {
    if (x->value > 0)
        x->covered_width = x->right - x->left;
    else {
        if (x->leftchild == NULL)
            x->covered_width = 0;
        else
            x->covered_width =
                x->leftchild->covered_width + x->rightchild->covered_width;
    }
}

static Node *build(int left, int right) {
    Node *x = new Node;
    if (left == right)
        x->left = x->right = left;
    else {
        int mid = (left + right) / 2;
        x->left = left;
        x->right = right;
        x->leftchild = build(left, mid);
        x->rightchild = build(mid + 1, right);
    }

    return x;
}

static void insert(Node *x, int left, int right, int mode) {
    if (x->right < left || x->left > right)
        return;
    if (left <= x->left && x->right <= right)
        x->value += mode;
    else {
        int mid = xs[(x->leftid + x->rightid) / 2];
        if (right <= mid)
            insert(x->leftchild, left, right, mode);
        else if (left > mid)
            insert(x->rightchild, left, right, mode);
        else {
            insert(x->leftchild, left, right, mode);
            insert(x->rightchild, left, right, mode);
        }
    }

    update(x);
}

static int query(Node *x) {
    return x->covered_width;
}

inline int hashing(int x) {
    return lower_bound(xs + 1, xs + pos + 1, x) - xs - 1;
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", x1 + i, y1 + i, x2 + i, y2 + i);
        xs[++pos] = x1[i];
        events[pos].y = y1[i];
        events[pos].left = x1[i];
        events[pos].right = x2[i] - 1;
        events[pos].type = EVENTTYPE_ENTER;
        xs[++pos] = x2[i] - 1;
        events[pos].y = y2[i];
        events[pos].left = x1[i];
        events[pos].right = x2[i] - 1;
        events[pos].type = EVENTTYPE_EXIT;
    }  // for

    sort(xs + 1, xs + pos + 1);
    sort(events + 1, events + pos + 1);
    cnt = unique(xs + 1, xs + pos + 1) - xs - 1;
    for (int i = 2; i <= cnt; i++) {
        width[i] = xs[i] - xs[i - 1];
    }  // for
    for (int i = 1; i <= pos; i++) {
        events[i].left = hashing(events[i].left);
        events[i].right = hashing(events[i].right);
    }  // for
    tree = build(1, cnt);
}

int main() {
    initialize();

    int lasty = INT_MIN;
    int size = 0;
    for (int i = 1; i <= pos;) {
        EventPoint &e = events[i];

        if (lasty > INT_MIN) {
            int delta_y = e.y - lasty;
            size += query(tree) * delta_y;
        }

        int current_y = e.y;
        for (; i <= pos && events[i].y == current_y; i++) {
            if (events[i].type == EVENTTYPE_ENTER) {
                insert(tree, events[i].left, events[i].right, 1);
            } else {
                insert(tree, events[i].left, events[i].right, -1);
            }
        }  // for

        lasty = current_y;
    }  // for

    printf("%d\n", size);

    return 0;
}  // function main
