#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <algorithm>
// #include <fstream>
// #include <sstream>

using namespace std;

struct Node;
int size_of(Node *h);

struct Node {
    Node(char _c) : c(_c), size(1), left(NULL), right(NULL), parent(NULL) {}

    char c;
    int size;
    Node *left;
    Node *right;
    Node *parent;

    void update() {
        size = size_of(left) + size_of(right) + 1;
    }

    // std::string to_dot_code() {
    //     stringstream buffer;

    //     buffer << reinterpret_cast<long long>(this);
    //     buffer << "[label=\"";
    //     if (c == '\\')
    //         buffer << "_1";
    //     else if (c == '/')
    //         buffer << "_2";
    //     else
    //         buffer << c;
    //     buffer << " (" << size << ")";
    //     buffer << "\"];\n";

    //     if (left != nullptr) {
    //         buffer << reinterpret_cast<long long>(this) << ":sw -> "
    //                << reinterpret_cast<long long>(left) << "[style=bold];\n";
    //     }

    //     if (right != nullptr) {
    //         buffer << reinterpret_cast<long long>(this) << ":se -> "
    //                << reinterpret_cast<long long>(right) <<
    //                "[style=bold];\n";
    //     }

    //     if (parent) {
    //         buffer << reinterpret_cast<long long>(this) << " -> "
    //                << reinterpret_cast<long long>(parent) << ";\n";
    //     }

    //     return buffer.str();
    // }
};  // struct Node

// static void _show(Node *h, stringstream &buffer) {
//     if (!h)
//         return;

//     buffer << h->to_dot_code();
//     _show(h->left, buffer);
//     _show(h->right, buffer);
// }

// static void show(Node *h) {
//     stringstream buffer;

//     buffer << "digraph{node[shape=circle];";
//     _show(h, buffer);
//     buffer << "}";

//     fstream file("/tmp/tree.tmp.dot", ios::trunc | ios::out);
//     file << buffer.str();
//     file.close();
//     system("showdot /tmp/tree.tmp.dot");
// }

int size_of(Node *h) {
    return h ? h->size : 0;
}

inline void left_rotate(Node *h) {
    Node *x = h->left;
    h->left = x->right;
    x->right = h;

    if (h->left)
        h->left->parent = h;

    x->parent = h->parent;
    h->parent = x;

    if (x->parent) {
        if (x->parent->left == h)
            x->parent->left = x;
        else
            x->parent->right = x;
    }

    h->update();
    x->update();
}

inline void right_rotate(Node *h) {
    Node *x = h->right;
    h->right = x->left;
    x->left = h;

    if (h->right)
        h->right->parent = h;

    x->parent = h->parent;
    h->parent = x;

    if (x->parent) {
        if (x->parent->left == h)
            x->parent->left = x;
        else
            x->parent->right = x;
    }

    h->update();
    x->update();
}

inline Node *splay(Node *x) {
    if (!x)
        return NULL;

    while (x->parent) {
        if (!x->parent->parent) {
            if (x == x->parent->left)
                left_rotate(x->parent);
            else
                right_rotate(x->parent);
        } else {
            if (x == x->parent->left) {
                if (x->parent == x->parent->parent->left) {
                    left_rotate(x->parent->parent);
                    left_rotate(x->parent);
                } else {
                    left_rotate(x->parent);
                    right_rotate(x->parent);
                }
            } else {
                if (x->parent == x->parent->parent->left) {
                    right_rotate(x->parent);
                    left_rotate(x->parent);
                } else {
                    right_rotate(x->parent->parent);
                    right_rotate(x->parent);
                }
            }
        }
    }  // while

    return x;
}

inline Node *_insert_back(Node *h, char c) {
    if (!h)
        return new Node(c);

    while (true) {
        if (h->right)
            h = h->right;
        else {
            h->right = new Node(c);
            h->right->parent = h;

            return h->right;
        }
    }
}

inline Node *insert_back(Node *h, char c) {
    Node *inserted = _insert_back(h, c);

    return splay(inserted);
}

inline Node *kth(Node *h, int k) {
    if (!h)
        return NULL;

    while (true) {
        if (k <= size_of(h->left)) {
            h = h->left;
        } else if (k > size_of(h->left) + 1) {
            k -= size_of(h->left) + 1;
            h = h->right;
        } else {
            return h;
        }
    }
}

typedef pair<Node *, Node *> NodePair;
static NodePair split(Node *h, int k) {
    Node *x = kth(h, k);
    h = splay(x);

    x = h->right;
    x->parent = NULL;
    h->right = NULL;
    h->update();

    return NodePair(h, x);
}

static Node *merge(Node *a, Node *b) {
    if (!a)
        return b;
    if (!b)
        return a;

    a->right = b;
    b->parent = a;
    a->update();

    return a;
}

static void print(Node *h) {
    if (!h)
        return;

    print(h->left);
    putchar(h->c);
    print(h->right);
}

static Node *tree;

int main() {
    tree = insert_back(tree, '#');
    tree = insert_back(tree, '$');

    char buffer[10];
    int k = 1;
    int t;
    scanf("%d", &t);
    while (t > 0) {
        scanf("%s", buffer);

        if (buffer[0] == 'P') {
            k--;
        } else if (buffer[0] == 'N') {
            k++;
        } else if (buffer[0] == 'M') {
            scanf("%d", &k);
            k++;
        } else if (buffer[0] == 'G') {
            int n;
            scanf("%d", &n);

            if (n > 0) {
                NodePair a = split(tree, k);
                NodePair b = split(a.second, n);

                print(b.first);
                putchar('\n');

                tree = merge(a.first, merge(b.first, b.second));
            }
        } else if (buffer[0] == 'D') {
            int n;
            scanf("%d", &n);
            if (n > 0) {
                NodePair a = split(tree, k);
                NodePair b = split(a.second, n);

                tree = merge(a.first, b.second);

                // show(tree);
            }
        } else {  // Insert
            int n;
            scanf("%d", &n);

            if (n > 0) {
                Node *para = NULL;

                getchar();  // ignore space.
                char c;
                while (n > 0) {
                    c = getchar();

                    if (c == '\n')
                        continue;

                    para = insert_back(para, c);

                    n--;
                }

                NodePair a = split(tree, k);
                tree = merge(a.first, para);
                right_rotate(tree);
                tree = merge(tree->parent, a.second);

                // show(tree);
            }
        }

        t--;
    }  // while

    return 0;
}  // function main
