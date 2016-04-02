// #define USE_FILE_IO
// #define NDEBUG

#include <cassert>
#include <cstring>
#include <climits>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

#ifndef USE_FILE_IO
#include <iostream>
using std::cin;
using std::cout;
#else
static ifstream cin("tree.in");
static ofstream cout("tree.out");
#endif  // IFNDEF USE_FILE_IO

inline void initialize() {
#ifndef USE_FILE_IO
    ios::sync_with_stdio(false);
#endif
};

struct Node {
    Node() = default;
    Node(int _key = 0, int _value = 0, int _weight = 0, Node *_left = nullptr,
         Node *_right = nullptr)
            : key(_key)
            , value(_value)
            , weight(_weight)
            , left(_left)
            , right(_right) {}

    int key = 0;
    int value = 0;
    int weight = 0;
    Node *left = nullptr;
    Node *right = nullptr;

    std::string print_node() {
        stringstream buffer;

        buffer << key;
        buffer << "[label=\"" << key << "/" << weight << "\"]";
        buffer << ";";

        if (left != nullptr) {
            buffer << key << ":sw -> " << left->key << ";";
        }

        if (right != nullptr) {
            buffer << key << ":se -> " << right->key << ";";
        }

        return buffer.str();
    }
};  // struct Node

struct MyRandom {
    MyRandom(const unsigned seed) {
        srand(seed);
    }

    auto operator()() -> int {
        return rand();
    }
};  // struct MyRandom

static Node *tree = nullptr;
static random_device rd;
static MyRandom randint(rd());

typedef pair<Node *, Node *> NodePair;

Node *insert(Node *h, int key, int value);
Node *remove(Node *h, int key);
int query(Node *h, int key);
NodePair nearest(Node *h, int target);

Node *right_rotate(Node *h);
Node *left_rotate(Node *h);
Node *balance(Node *h);

void print_tree(Node *node);
void print_tree(Node *node, std::string &data);

int main() {
    initialize();

    char command;
    int key = INT_MAX, value = INT_MAX;
    while (cin >> command) {
        switch (command) {
            case 'A':
                cin >> key >> value;
                tree = insert(tree, key, value);

                break;
            case 'D':
                cin >> key;
                tree = remove(tree, key);

                break;
            case 'Q':
                cin >> key;
                cout << query(tree, key) << "\n";

                break;

            case 'N':
                cin >> key;

                NodePair result = nearest(tree, key);
                Node *a = result.first, *b = result.second;

                if (a == nullptr) {
                    cout << b->key << "\n";
                } else if (b == nullptr) {
                    cout << a->key << "\n";
                } else {
                    cout << min(a->key, b->key,
                                [key](const int &_a, const int &_b) {
                                    return abs(key - _a) < abs(key - _b);
                                }) << "\n";
                }

                break;
        }  // switch to command

#ifndef NDEBUG
        // if (command == 'A') {
        //     cout << "A " << key << " " << value << endl;
        // }
        // if (command == 'D') {
        //     cout << "D " << key << endl;
        // }

        if (command == 'P') {
            print_tree(tree);
        }
#endif  // IFNDEF NDEBUG
    }   // while

    return 0;
}  // function main

void print_tree(Node *node) {
    std::string data;
    data = "digraph{\nnode [shape=circle];";

    print_tree(node, data);

    data += "}";
    ofstream file("/tmp/tree.tmp.dot");
    file << data;
    file.close();
    system("showdot /tmp/tree.tmp.dot");
}

void print_tree(Node *node, std::string &data) {
    if (node == nullptr)
        return;

    data += node->print_node();
    print_tree(node->left, data);
    print_tree(node->right, data);
}

Node *insert(Node *h, int key, int value) {
    if (h == nullptr)
        return new Node(key, value, randint());

    if (key < h->key) {
        h->left = insert(h->left, key, value);

        if (h->left->weight < h->weight) {
            h = right_rotate(h);
        }
    } else if (key > h->key) {
        h->right = insert(h->right, key, value);

        if (h->right->weight < h->weight) {
            h = left_rotate(h);
        }
    } else {
        h->value = value;
    }

    return h;
}

static Node *remove(Node *h) {
    if (h->left != nullptr and h->right != nullptr) {
        if (h->left->weight >= h->right->weight) {
            h = right_rotate(h);

            h->right = remove(h->right);
        } else {
            h = left_rotate(h);

            h->left = remove(h->left);
        }
    } else {
        Node *next = nullptr;

        if (h->left != nullptr) {
            next = h->left;
        } else {
            next = h->right;
        }

        delete h;
        return next;
    }

    return h;
}

Node *remove(Node *h, int key) {
    assert(h != nullptr);

    if (key < h->key) {
        h->left = remove(h->left, key);
    } else if (key > h->key) {
        h->right = remove(h->right, key);
    } else {
        return remove(h);
    }

    return h;
}

int query(Node *h, int key) {
    Node *current = h;
    while (current != nullptr and current->key != key) {
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    return current != nullptr ? current->value : -1;
}

NodePair nearest(Node *h, int target) {
    Node *current = h;
    Node *left = nullptr;
    Node *right = nullptr;

    while (current != nullptr and target != current->key) {
        if (target < current->key) {
            right = current;
            current = current->left;
        } else if (target > current->key) {
            left = current;
            current = current->right;
        }
    }

    if (current != nullptr and target == current->key) {
        left = right = current;
    }

    return NodePair(left, right);
}

Node *right_rotate(Node *h) {
    assert(h != nullptr);
    assert(h->left != nullptr);

    Node *x = h->left;
    h->left = x->right;
    x->right = h;

    return x;
}

Node *left_rotate(Node *h) {
    assert(h != nullptr);
    assert(h->right != nullptr);

    Node *x = h->right;
    h->right = x->left;
    x->left = h;

    return x;
}
