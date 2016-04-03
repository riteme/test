// #define USE_FILE_IO
// #define NDEBUG

#include <cstring>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <functional>
#include <unordered_map>
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

static void initialize() {
#ifndef USE_FILE_IO
    ios::sync_with_stdio(false);
#endif

    cin.tie(0);
    cout.tie(0);
};

struct MyRandom {
    MyRandom() {
        srand(time(0));
    }

    int operator()() const {
        return rand();
    }
};  // struct MyRandom

static MyRandom randint;

struct Node {
    Node(int _key = 9, int _value = 0, Node *_left = nullptr,
         Node *_right = nullptr)
            : key(_key)
            , value(_value)
            , weight(randint())
            , left(_left)
            , right(_right) {
        update();
    }

    ~Node() {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }

    int key;
    int value;
    int weight;
    int size;
    Node *left;
    Node *right;

    void update() {
        size = 1 + (left == nullptr ? 0 : left->size) +
               (right == nullptr ? 0 : right->size);
    }

    string print_node() {
        stringstream buffer;

        buffer << key;
        buffer << "[label=\"" << key << ": " << value << "\"]";
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

static void print_tree(Node *node, std::string &data) {
    if (node == nullptr)
        return;

    data += node->print_node();
    print_tree(node->left, data);
    print_tree(node->right, data);
}

static string print_tree(Node *node) {
    std::string data;

    print_tree(node, data);

    return data;
}

static void showdot(const string &data) {
    ofstream f("/tmp/tree.tmp.dot");
    f << data;
    f.close();
    system("showdot /tmp/tree.tmp.dot");
}

typedef Node *Treap;
typedef pair<Treap, Treap> TreapPair;
typedef function<void(void)> OperationType;

void print_all_treap();
void print_treap();
void resize();
void new_node();
void split_treap();
void merge_treap();
void query_node();
void insert_node();
void remove_node();

static unordered_map<string, OperationType> function_map = {
    { "print_all", print_all_treap },
    { "print", print_treap },
    { "resize", resize },
    { "new", new_node },
    { "split", split_treap },
    { "merge", merge_treap },
    { "query", query_node },
    { "insert", insert_node },
    { "remove", remove_node }
};

static vector<Treap> trees = { nullptr };

int main() {
    initialize();

    string command;
    while (cin >> command) {
        function_map[command]();
    }  // while

    return 0;
}  // function main

void print_all_treap() {
    string source = "digraph{\nnode [shape=circle];";

    for (auto treap : trees) {
        source += print_tree(treap);
    }  // foreach in trees

    source += "}";

    showdot(source);
}

void print_treap() {
    int id;
    cin >> id;

    string source = "digraph{\nnode [shape=circle];";
    source += print_tree(trees[id]);
    source += "}";
    showdot(source);
}

void resize() {
    int size;
    cin >> size;

    trees.resize(size);
}

void new_node() {
    int id, key, value;
    cin >> id >> key >> value;

    trees[id - 1] = new Node(key, value);
}

void split_treap() {}

void merge_treap() {}

void query_node() {}

void insert_node() {}

void remove_node() {}
