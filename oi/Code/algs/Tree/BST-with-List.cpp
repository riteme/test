#include <bits/stdc++.h>

using namespace std;

#define SEED (233)
static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;

struct Node {
    Node(int _key)
            : weight(randint())
            , key(_key)
            , left(NULL)
            , right(NULL)
            , prev(NULL)
            , next(NULL) {}

    int weight;
    int key;
    Node *left;
    Node *right;
    Node *prev;
    Node *next;
};  // struct Node

inline Node *left_rotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    return x;
}

inline Node *right_rotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

static Node *insert(Node *x, int key) {
    if (!x)
        return new Node(key);

    if (key < x->key) {
        x->left = insert(x->left, key);

        if (!x->left->prev) {  // No links set
            x->left->next = x;
            x->left->prev = x->prev;

            if (x->prev)
                x->prev->next = x->left;
            x->prev = x->left;
        }

        if (x->left->weight < x->weight)
            return left_rotate(x);
    } else {
        x->right = insert(x->right, key);

        if (!x->right->prev) {
            x->right->next = x->next;
            x->right->prev = x;

            x->next = x->right;
            if (x->next)
                x->next->prev = x->right;
        }
    }

    return x;
}

static Node *query(Node *x, int key) {
    if (!x)
        return NULL;

    if (key < x->key)
        return query(x->left, key);
    else if (key > x->key)
        return query(x->right, key);
    else
        return x;
}

int main() {
    char buffer[10];
    int x;

    Node *tree = NULL;
    while (scanf("%s%d", buffer, &x) != EOF) {
        if (buffer[0] == 'A') {
            tree = insert(tree, x);
        } else if (buffer[0] == 'Q') {
            Node *n = query(tree, x);

            if (n) {
                while (n) {
                    printf("%d ", n->key);
                    n = n->next;
                }  // while
                putchar('\n');
            }
        } else {
            printf("Unknown\n");
        }
    }  // while

    return 0;
}  // function main
