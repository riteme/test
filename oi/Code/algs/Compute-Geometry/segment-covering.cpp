#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

struct Node {
    Node() : value(0), covered_width(0), leftchild(NULL), rightchild(NULL) {}

    int left, right;
    int value;
    int covered_width;

    Node *leftchild, *rightchild;
};  // struct Node

inline void update(Node *x) {
    if (x->value > 0)
        x->covered_width = x->right - x->left + 1;
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
        int mid = (x->left + x->right) / 2;
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

static Node *tree;

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    tree = build(1, n);

    for (int cnt = 0; cnt < q; cnt++) {
        char buffer[10];
        int x, y;
        scanf("%s%d%d", buffer, &x, &y);

        if (buffer[0] == 'A')
            insert(tree, x, y, 1);
        else
            insert(tree, x, y, -1);
        printf("%d\n", tree->covered_width);
    }  // for

    return 0;
}  // function main
