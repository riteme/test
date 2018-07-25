// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

struct Node;
int size_of(Node *x);
int min_of(Node *x);

struct Node {
    struct Mark {
        Mark() : sum(0), reversed(false) {}

        int sum;
        bool reversed;

        bool empty() {
            return sum == 0 && !reversed;
        }
    };  // struct Mark

    Node(int n)
            : number(n)
            , min(INT_MAX)
            , size(1)
            , left(NULL)
            , right(NULL)
            , parent(NULL) {}

    int number;
    int min;
    int size;
    Mark mark;
    Node *left;
    Node *right;
    Node *parent;

    void update() {
        assert(mark.sum == 0);

        size = size_of(left) + size_of(right) + 1;
        min = std::min(number, std::min(min_of(left), min_of(right)));
    }

    void pushdown() {
        if (mark.sum > 0) {
            number += mark.sum;

            if (left)
                left->mark.sum += mark.sum;
            if (right)
                right->mark.sum += mark.sum;

            mark.sum = 0;
            update();
        }

        if (mark.reversed) {
            mark.reversed = false;

            if (left)
                left->mark.reversed = !left->mark.reversed;
            if (right)
                right->mark.reversed = !right->mark.reversed;

            swap(left, right);
        }
    }

    std::string print_node() {
        stringstream buffer;

        buffer << reinterpret_cast<long long>(this);
        buffer << "[label=\"" << number << "\\n(" << min << ", " << mark.sum
               << ")"
               << "\"";
        if (mark.reversed)
            buffer << " color=red";
        buffer << "];";

        if (left != nullptr) {
            buffer << reinterpret_cast<long long>(this) << ":sw -> "
                   << reinterpret_cast<long long>(left) << "[style=bold];";
        }

        if (right != nullptr) {
            buffer << reinterpret_cast<long long>(this) << ":se -> "
                   << reinterpret_cast<long long>(right) << "[style=bold];";
        }

        if (parent != nullptr) {
            buffer << reinterpret_cast<long long>(this) << " -> "
                   << reinterpret_cast<long long>(parent) << ";";
        }

        return buffer.str();
    }
};  // struct Node

static void print_tree(Node *node, std::string &data, int sum = 0) {
    if (node == nullptr)
        return;

    data += node->print_node();
    print_tree(node->left, data, sum + node->mark.sum);
    printf("%d ", node->number + sum);
    print_tree(node->right, data, sum + node->mark.sum);
}

static void show(Node *node) {
    std::string data;
    data = "digraph{\nnode [shape=circle];";

    print_tree(node, data, node->mark.sum);

    data += "}";
    ofstream file("/tmp/tree.tmp.dot");
    file << data;
    file.close();
    // system("showdot /tmp/tree.tmp.dot");
    putchar('\n');
}

inline int size_of(Node *x) {
    return x ? x->size : 0;
}

inline int min_of(Node *x) {
    return x ? x->min + x->mark.sum : INT_MAX;
}

inline Node *left_rotate(Node *h) {
    assert(h != NULL);
    assert(h->left != NULL);

    Node *x = h->left;
    h->pushdown();
    x->pushdown();

    x->parent = h->parent;
    h->parent = x;
    if (x->right)
        x->right->parent = h;
    if (x->parent) {
        if (x->parent->left == h)
            x->parent->left = x;
        else
            x->parent->right = x;
    }

    h->left = x->right;
    x->right = h;

    h->update();
    x->update();

    return x;
};

inline Node *right_rotate(Node *h) {
    assert(h != NULL);
    assert(h->right != NULL);

    Node *x = h->right;
    h->pushdown();
    x->pushdown();

    x->parent = h->parent;
    h->parent = x;
    if (x->left)
        x->left->parent = h;
    if (x->parent) {
        if (x->parent->left == h)
            x->parent->left = x;
        else
            x->parent->right = x;
    }

    h->right = x->left;
    x->left = h;

    h->update();
    x->update();

    return x;
}

inline Node *kth(Node *h, int k) {
    if (!h)
        return NULL;

    while (k != size_of(h->left) + 1) {
        if (k < size_of(h->left) + 1) {
            h = h->left;
        } else {  // k > size_of(h->left) + 1
            k -= size_of(h->left) + 1;
            h = h->right;
        }
    }

    return h;
}

static Node *splay(Node *x) {
    if (!x)
        return NULL;

    while (x->parent) {
        if (x->parent->parent) {
            if (x->parent->left == x) {
                if (x->parent->parent->left == x->parent) {  // LL
                    left_rotate(x->parent->parent);
                    left_rotate(x->parent);
                } else {  // x->parent->parent->right == x->parent  // LR
                    left_rotate(x->parent);
                    right_rotate(x->parent);
                }
            } else {  // x->parent->right == x
                if (x->parent->parent->left == x->parent) {  // RL
                    right_rotate(x->parent);
                    left_rotate(x->parent);
                } else {  // x->parent->parent->right == x->parent  // RR
                    right_rotate(x->parent->parent);
                    right_rotate(x->parent);
                }
            }
        } else {                         // No grandfather
            if (x->parent->left == x) {  // L
                left_rotate(x->parent);
            } else {  // x->parent->left == x  // R
                right_rotate(x->parent);
            }
        }
    }

    return x;
}

typedef pair<Node *, Node *> NodePair;
static NodePair split(Node *h, int k) {
    h = splay(kth(h, k));

    assert(h->mark.empty());
    NodePair result = make_pair(h, h->right);
    h->right->parent = NULL;
    h->right = NULL;
    h->update();

    return result;
}

static Node *merge(Node *a, Node *b) {
    if (!a)
        return b;
    if (!b)
        return a;

    assert(a->right == NULL);
    a->pushdown();
    a->right = b;
    b->parent = a;
    a->update();

    return a;
}

static Node *insert_back(Node *h, int number) {
    if (!h)
        return new Node(number);

    Node *last = NULL;
    while (h) {
        last = h;
        h = h->right;
    }

    assert(last != NULL);
    Node *x = new Node(number);
    last->right = x;
    x->parent = last;
    last->update();

    return splay(x);
}

inline Node *make_splay() {
    Node *tree = new Node(INT_MAX);
    tree->left = new Node(INT_MAX);
    tree->left->parent = tree;
    tree->update();

    return tree;
}

int main() {
    int n, m;
    Node *tree = make_splay();

    // Initialize the sequence
    scanf("%d", &n);
    Node *initial = NULL;
    while (n > 0) {
        int a;
        scanf("%d", &a);
        initial = insert_back(initial, a);

        n--;
    }
    tree->left->right = initial;
    initial->parent = tree->left;
    tree->left->update();
    tree->update();

    scanf("%d", &m);
    char buffer[10];
    while (m > 0) {
        scanf("%s", buffer);

        if (buffer[0] == 'A') {
            int x, y, d;
            scanf("%d%d%d", &x, &y, &d);

            NodePair a = split(tree, x);
            NodePair b = split(a.second, y - x + 1);
            b.first->mark.sum += d;

            tree = merge(a.first, merge(b.first, b.second));
            show(tree);
        } else if (buffer[0] == 'I') {
            int x, p;
            scanf("%d%d", &x, &p);

            NodePair a = split(tree, x + 1);
            a.first = insert_back(a.first, p);
            tree = merge(a.first, a.second);
            show(tree);
        } else if (buffer[0] == 'D') {
            int x;
            scanf("%d", &x);

            NodePair a = split(tree, x);
            NodePair b = split(a.second, 1);
            tree = merge(a.first, b.second);
            show(tree);
        } else if (buffer[0] == 'M') {
            int x, y;
            scanf("%d%d", &x, &y);

            show(tree);
            NodePair a = split(tree, x);
            NodePair b = split(a.second, y - x + 1);

            printf("%d\n", min_of(b.first));

            tree = merge(a.first, merge(b.first, b.second));
        } else {  // R
            if (strcmp(buffer, "REVERSE") == 0) {
                int x, y;
                scanf("%d%d", &x, &y);

                NodePair a = split(tree, x);
                NodePair b = split(a.second, y - x + 1);

                while (b.first->left)
                    b.first = b.first->left;
                b.first = splay(b.first);
                swap(b.first->left, b.first->right);
                b.first->left->mark.reversed = !b.first->left->mark.reversed;

                tree = merge(a.first, merge(b.first, b.second));
                show(tree);
            } else {  // REVOLVE
                int x, y, t;
                scanf("%d%d%d", &x, &y, &t);

                if (t < 0)
                    t = (y - x + 1) - (-t % (y - x + 1));
                else
                    t %= (y - x + 1);
                printf("t = %d\n", t);

                if (t != 0) {
                    NodePair a = split(tree, x);
                    NodePair b = split(a.second, y - x + 1);
                    NodePair c = split(b.first, y - x + 1 - t);

                    if (c.second->right) {
                        Node *node = c.second->right;
                        while (node->right)
                            node = node->right;

                        assert(node->right == NULL);
                        c.second = splay(node);
                    }

                    assert(c.second->right == NULL);
                    b.first = merge(c.second, c.first);
                    b.first = right_rotate(b.first);

                    assert(b.first->right == NULL);
                    tree = merge(a.first, merge(b.first, b.second));
                }

                show(tree);
            }
        }

        m--;
    }  // while

    return 0;
}  // function main
