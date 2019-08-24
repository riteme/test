#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <algorithm>

using namespace std;

static void initialize() {}

struct MyRandom {
    MyRandom() {
        srand(233);
    }

    int operator()() const {
        return rand();
    }
};  // struct MyRandom

static MyRandom randint;

struct Node;
int size_of(Node *h);

struct Node {
    Node(char _c)
            : c(_c), size(1), weight(randint()), left(NULL), right(NULL) {}

    char c;
    int size;
    int weight;
    Node *left;
    Node *right;

    void update() {
        size = size_of(left) + size_of(right) + 1;
    }
};  // struct Node

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

static Node *merge(Node *a, Node *b) {
    if (!a)
        return b;
    if (!b)
        return a;

    if (a->weight > b->weight) {
        b->left = merge(a, b->left);
        b->update();

        // return balance(b);
        return b;
    } else {
        a->right = merge(a->right, b);
        a->update();

        // return balance(a);
        return a;
    }
}

inline Node *right_rotate(Node *h) {
    Node *x = h->right;
    h->right = x->left;
    x->left = h;

    h->update();
    x->update();

    return x;
}

static Node *insert_back(Node *h, char c) {
    if (h == NULL) {
        return new Node(c);
    }

    h->right = insert_back(h->right, c);

    if (h->right->weight < h->weight) {
        return right_rotate(h);
    }

    h->update();
    return h;
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

                para = insert_back(para, c);

                n--;
            }

            NodePair a = split(tree, k);
            tree = merge(merge(a.first, para), a.second);
        }

        t--;
    }  // while

    return 0;
}  // function main
