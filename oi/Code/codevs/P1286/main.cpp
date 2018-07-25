#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

#define OP_INIT 'I'
#define OP_INC 'A'
#define OP_DEC 'S'
#define OP_QUERY 'F'

struct Node {
    Node() : key(0), size(0), weight(0), left(NULL), right(NULL) {}
    Node(int _key, int _size = 1, Node *_left = NULL, Node *_right = NULL)
            : key(_key)
            , size(_size)
            , weight(rand())
            , left(_left)
            , right(_right) {}

    int key;
    int size;
    int weight;
    Node *left;
    Node *right;

    void update() {
        size = 1;
        if (left != NULL)
            size += left->size;
        if (right != NULL)
            size += right->size;
    }
};  // struct Node

static int n, m;
static Node *tree = NULL;
static vector<int> kickoff;
static int kicked = 0;
static int tree_size = 0;

Node *insert(Node *h, int key);
Node *remove(Node *h, int key);
Node *modify(Node *h, int value);
Node *rank_min(Node *h, int k);
Node *rank_max(Node *h, int k);

static void initialize() {
    scanf("%d%d", &n, &m);
    srand(145647U);
}

int main() {
    initialize();

    for (int i = 0; i < n; ++i) {
        char q = getchar();
        while (q < 'A' or q > 'Z')
            q = getchar();

        int k;
        scanf("%d", &k);
        switch (q) {
            case OP_INIT:
                if (k >= m)
                    tree = insert(tree, k);
                break;
            case OP_INC: tree = modify(tree, k); break;
            case OP_DEC: tree = modify(tree, -k); break;
            case OP_QUERY:
                Node *person = rank_max(tree, k);

                if (person == NULL)
                    printf("-1\n");
                else
                    printf("%d\n", person->key);

                break;
        }  // switch to q
    }      // for

    printf("%d", kicked);

    return 0;
}  // function main

static Node *left_rotate(Node *h) {
    Node *x = h->left;
    h->left = x->right;
    x->right = h;

    return x;
}

static Node *right_rotate(Node *h) {
    Node *x = h->right;
    h->right = x->left;
    x->left = h;

    return x;
}

Node *insert(Node *h, int key) {
    if (h == NULL) {
        tree_size++;
        return new Node(key);
    }

    if (key < h->key) {
        h->left = insert(h->left, key);

        if (h->left->weight < h->weight) {
            h = left_rotate(h);
            h->right->update();
        }

        h->update();
    } else {
        h->right = insert(h->right, key);

        if (h->right->weight < h->weight) {
            h = right_rotate(h);
            h->left->update();
        }

        h->update();
    }

    return h;
}

static Node *_remove(Node *h) {
    if (h->left != NULL and h->right != NULL) {
        if (h->left->weight < h->right->weight) {
            h = left_rotate(h);

            h->right = _remove(h->right);
        } else {
            h = right_rotate(h);

            h->left = _remove(h->left);
        }
    } else {
        Node *next;

        if (h->left != NULL)
            next = h->left;
        else
            next = h->right;

        delete h;
        tree_size--;

        return next;
    }

    h->update();
    return h;
}

Node *remove(Node *h, int key) {
    if (key < h->key) {
        h->left = remove(h->left, key);
    } else if (key > h->key) {
        h->right = remove(h->right, key);
    } else {
        return _remove(h);
    }

    h->update();
    return h;
}

static void _modify(Node *h, int value) {
    if (h == NULL)
        return;

    h->key += value;
    if (h->key < m)
        kickoff.push_back(h->key);

    _modify(h->left, value);
    _modify(h->right, value);
}

Node *modify(Node *h, int value) {
    kickoff.clear();

    _modify(h, value);

    for (unsigned i = 0; i < kickoff.size(); i++) {
        h = remove(h, kickoff[i]);
        kicked++;
    }

    return h;
}

Node *rank_max(Node *h, int k) {
    return rank_min(h, tree_size - k + 1);
}

Node *rank_min(Node *h, int k) {
recursive:
    if (h == NULL)
        return NULL;

    int lsize;
    if (h->left == NULL)
        lsize = 0;
    else
        lsize = h->left->size;

    if (lsize == k - 1)
        return h;
    else if (lsize < k - 1) {
        // return rank_min(h->right, k - lsize - 1);
        h = h->right;
        k = k - lsize - 1;
        goto recursive;
    } else {
        // return rank_min(h->left, k);
        h = h->left;
        goto recursive;
    }
}
