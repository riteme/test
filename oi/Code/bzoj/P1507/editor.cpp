#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
// #include <fstream>
// #include <sstream>

using namespace std;

static void initialize() {}

struct Node;
int rank_of(Node *h);
int size_of(Node *h);

struct Node {
    Node(char _c) : c(_c), rank(1), size(1), left(NULL), right(NULL) {}

    char c;
    int rank;
    int size;
    Node *left;
    Node *right;

    void update() {
        rank = max(rank_of(left), rank_of(right)) + 1;
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
    //     buffer << "\"];\n";

    //     if (left != nullptr) {
    //         buffer << reinterpret_cast<long long>(this) << ":sw -> "
    //                << reinterpret_cast<long long>(left) << ";\n";
    //     }

    //     if (right != nullptr) {
    //         buffer << reinterpret_cast<long long>(this) << ":se -> "
    //                << reinterpret_cast<long long>(right) << ";\n";
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

int rank_of(Node *h) {
    return h ? h->rank : 0;
}

int size_of(Node *h) {
    return h ? h->size : 0;
}

typedef pair<Node *, Node *> NodePair;
static NodePair split(Node *h, int k) {
    if (!h)
        return NodePair(NULL, NULL);

    NodePair a;
    if (k <= size_of(h->left)) {
        a = split(h->left, k);
        h->left = a.second;
        h->update();

        return NodePair(a.first, h);
    } else {
        a = split(h->right, k - size_of(h->left) - 1);
        h->right = a.first;
        h->update();

        return NodePair(h, a.second);
    }
}

static int ap, bp;
static Node *_merge(Node *a, Node *b) {
    if (!a)
        return b;
    if (!b)
        return a;

    int sit1 = rank_of(a->right) + b->rank;
    int sit2 = rank_of(b->left) + a->rank;
    if (sit1 < sit2 || (sit1 == sit2 && ap < bp)) {
        ap++;
        a->right = _merge(a->right, b);
        a->update();

        return a;
    } else {
        bp++;
        b->left = _merge(a, b->left);
        b->update();

        return b;
    }
}

static Node *merge(Node *a, Node *b) {
    ap = bp = 0;
    return _merge(a, b);
}

static void print(Node *h) {
    if (!h)
        return;

    print(h->left);
    putchar(h->c);
    print(h->right);
}

static Node *tree;
static char buf[1000000];

int main() {
    initialize();

    char buffer[10];
    int k = 0;
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
        } else if (buffer[0] == 'G') {
            int n;
            scanf("%d", &n);

            NodePair a = split(tree, k);
            NodePair b = split(a.second, n);
            print(b.first);
            putchar('\n');

            tree = merge(a.first, merge(b.first, b.second));
        } else if (buffer[0] == 'D') {
            int n;
            scanf("%d", &n);

            NodePair a = split(tree, k);
            NodePair b = split(a.second, n);
            tree = merge(a.first, b.second);
        } else {  // Insert
            int n;
            scanf("%d", &n);
            Node *para = NULL;

            char c;
            while (n > 0) {
                c = getchar();

                if (c == '\n')
                    continue;

                para = merge(para, new Node(c));

                n--;
            }

            NodePair a = split(tree, k);
            tree = merge(merge(a.first, para), a.second);
            // show(tree);
        }

        t--;
    }  // while

    return 0;
}  // function main
