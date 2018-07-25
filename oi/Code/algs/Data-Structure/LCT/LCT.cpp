#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

/**
 * Splay tree
 */
namespace Splay {

/**
 * Respect a null node
 */
struct Node;
static Node *null;

struct Node {
    struct Mark {
        bool reversed = false;

        bool empty() const {
            return !reversed;
        }
    };  // struct Mark

    int key = 0;

    int size = 1;

    Mark mark;

    int path_parent = 0;

    Node *left = null;
    Node *right = null;
    Node *parent = null;
};  // struct Node

inline void initialize_null_node() {
    null = new Node;
    null->size = 0;
    null->left = null;
    null->right = null;
    null->parent = null;
}

inline void pushdown(Splay::Node *x) {
    if (x->mark.reversed) {
        swap(x->left, x->right);
        x->left->mark.reversed = x->right->mark.reversed = true;
        x->mark.reversed = false;
    }
}

inline void update(Splay::Node *x) {
    x->size = x->left->size + x->right->size + 1;
}

inline Node *left_rotate(Splay::Node *x) {
    assert(x != null);
    assert(x->left != null);
    assert(x->mark.empty());
    assert(->left->mark.empty());

    Node *y = x->left;
    x->left = y->right;
    y->right = x;

    if (x->parent != null) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        y->path_parent = x->path_parent;
    }

    y->parent = x->parent;
    x->parent = y;
    x->left->parent = x;

    update(x);
    update(y);

    return y;
}

inline Node *right_rotate(Splay::Node *x) {
    assert(x != null);
    assert(x->right != null);
    assert(x->mark.empty());
    assert(x->right->mark.empty());

    Node *y = x->right;
    x->right = y->left;
    y->left = x;

    if (x->parent != null) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        y->path_parent = x->path_parent;
    }

    y->parent = x->parent;
    x->parent = y;
    x->right->parent = x;

    update(x);
    update(y);

    return y;
}

static Node *splay(Splay::Node *x) {
    while (x->parent != null) {
        Node *p1 = x->parent;
        Node *p2 = p1->parent;

        if (p2 == null) {
            if (x == p1->left) {  // L
                left_rotate(p1);
            } else {  // R
                right_rotate(p1);
            }
        } else {
            if (x == p1->left) {
                if (p1 == p2->left) {  // LL
                    left_rotate(p2);
                    left_rotate(p1);
                } else {  // LR
                    left_rotate(p1);
                    right_rotate(p2);
                }
            } else {
                if (p1 == p2->left) {  // RL
                    right_rotate(p1);
                    left_rotate(p2);
                } else {  // RR
                    right_rotate(p2);
                    right_rotate(p1);
                }
            }
        }
    }  // while

    return x;
}

static Node *splay_at(Splay::Node *x, int key) {
    while (x != null && key != x->key) {
        if (key < x->key)
            x = x->left;
        else if (key > x->key)
            x = x->right;
    }  // while

    return splay(x);
}

static bool contain(Splay::Node *x, int key) {
    while (x->parent != null) {
        if (x == x->parent->right) {
            return x->parent;
        }

        x = x->parent;
    }  // while

    while (x != null) {
        if (key < x->key) {
            x = x->left;
        } else if (key > x->key) {
            x = x->right;
        } else {
            return true;
        }
    }  // while

    return false;
}

}  // namespace Splay

namespace LCT {
constexpr int NMAX = 20;
struct Node;
static Node *nodes[NMAX + 1];

struct Node {
    Node(int _key) {
        key = _key;
        external->key = key;
        external->path_parent = 0;
    }

    int key;

    Node *parent = NULL;
    Splay::Node *external = new Splay::Node;
};  // struct Node

inline void construct_nodes() {
    for (int i = 1; i <= NMAX; i++) {
        nodes[i] = new Node(i);
    }  // for
}

/**
 * Split a chain into two parts, one includes node x
 * @param x split point
 */
inline void disconnect(LCT::Node *x) {
    assert(x != NULL);

    Splay::splay(x->external);

    if (x->external->right != Splay::null) {
        x->external->right->parent = Splay::null;
        x->external->right->path_parent = x->key;
        x->external->right = Splay::null;
        Splay::update(x->external);
    }
}

/**
 * Connect two chains
 * @param p endpoint of the first chain
 * @param x beginning of the second chain
 */
inline void connect(LCT::Node *p, LCT::Node *x) {
    assert(p != NULL);
    assert(x != NULL);
    assert(p->external->right == null);
    assert(x->external->parent == null);

    p->external->right = x->external;
    x->external->parent = p->external;
    Splay::update(p->external);
}

static void access(LCT::Node *x) {
    disconnect(x);

    while (x->external->path_parent != 0) {
        cout << x->external->path_parent << endl;
        Node *pparent = nodes[x->external->path_parent];

        disconnect(pparent);
        connect(pparent, x);

        assert(pparent->external->parent == Splay::null);
        x = pparent;
    }  // while

    puts("access completed");
}

static void access(int x) {
    access(nodes[x]);
}

static ostream &operator<<(ostream &stream, const LCT::Node *x) {
    stream << x->key << ";\n";

    if (x->parent) {
        stream << x->parent->key << " -> " << x->key;

        if (!Splay::contain(x->external, x->parent->key)) {
            stream << "[ style = dashed ]";
        } else {
            stream << "[ style = bold ]";
        }

        stream << ";\n";
    }

    return stream;
}

static void show_all() {
    ostringstream buffer;

    buffer << "digraph {\n";
    buffer << "node [ shape = circle ];\n";
    for (int i = 1; i <= NMAX; i++) {
        buffer << nodes[i];
    }  // for
    buffer << "}\n";

    ofstream script("/tmp/lct.dot");
    assert(script.is_open());
    script << buffer.str();
    script.close();

    system("dot /tmp/lct.dot -Tsvg > /tmp/lct.svg && eog /tmp/lct.svg &");
}

}  // namespace LCT

/**
 * Global initialization & cleanup
 */
static struct __Runtime {
    __Runtime() {
        ios::sync_with_stdio(false);
        Splay::initialize_null_node();
        LCT::construct_nodes();
    }

    ~__Runtime() {}
} __init;  // struct __Runtime

int main() {
    char command;
    while (cin >> command) {
        switch (command) {
            case 'P': {
                LCT::show_all();
            } break;

            case 'L': {
                int x, y;
                cin >> x >> y;

                LCT::nodes[y]->parent = LCT::nodes[x];
                LCT::nodes[y]->external->path_parent = x;
            } break;

            case 'A': {
                int x;
                cin >> x;

                LCT::access(x);
            } break;

        }  // switch to command

        LCT::show_all();
    }  // while

    return 0;
}  // function main
