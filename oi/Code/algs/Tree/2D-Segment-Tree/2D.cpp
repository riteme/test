#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

struct Node {
    Node()
            : x1(0)
            , x2(0)
            , y1(0)
            , y2(0)
            , sum(0)
            , c1(NULL)
            , c2(NULL)
            , c3(NULL)
            , c4(NULL) {}

    int x1, x2, y1, y2;
    int sum;

    Node *c1, *c2, *c3, *c4;
};  // struct Node

struct Rectangle {
    int x1, x2, y1, y2;

    bool empty() const {
        return x1 == x2 || y1 == y2;
    }
};  // struct Rectangle

inline void split(const Rectangle &target, Rectangle &c1, Rectangle &c2,
                  Rectangle &c3, Rectangle &c4) {
    int midx = (target.x1 + target.x2) / 2;
    int midy = (target.y1 + target.y2) / 2;

    c1 = { target.x1, midx, target.y1, midy };
    c2 = { midx + 1, target.x2, target.y1, midy };
    c3 = { target.x1, midx, midy + 1, target.y2 };
    c4 = { midx + 1, target.x2, midy + 1, target.y2 };
}

static Node *build(const Rectangle &rect) {
    if (rect.empty()) {
        return NULL;
    }

    Rectangle c1, c2, c3, c4;
    split(rect, c1, c2, c3, c4);
    Node *x = new Node;
    x->x1 = rect.x1;
    x->x2 = rect.x2;
    x->y1 = rect.y1;
    x->y2 = rect.y2;
    x->c1 = build(c1);
    x->c2 = build(c2);
    x->c3 = build(c3);
    x->c4 = build(c4);

    return x;
}

static void modify(Node *x, int x1, int y1, int v) {
    if (!x) {
        return;
    }
}
