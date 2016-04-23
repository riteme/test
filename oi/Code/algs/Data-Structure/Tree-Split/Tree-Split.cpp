#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

#define NMAX 1000

struct Node {
    int key;
    Node *father;
    Node *top;
    Node *next;
    int size;
    int depth;
    int id;

    vector<Node *> children;
};  // struct Node

static vector<Node *> nodes;
static vector<Node *> G[NMAX + 10];

static void read_graph() {
    int n;
    scanf("%d", &n);

    nodes.resize(n + 1);
    for (unsigned i = 1; i <= n; i++) {
        nodes[i] = new Node;
        nodes[i]->key = i;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(nodes[v]);
        G[v].push_back(nodes[u]);
    }  // for
}

static bool marked[NMAX];

static void make_tree(Node *u) {
    u->size = 1;
    u->next = NULL;

    for (auto v : G[u->key]) {
        if (!marked[v->key]) {
            marked[v->key] = true;

            v->father = u;
            v->depth = u->depth + 1;

            make_tree(v);

            u->size += v->size;

            if (!u->next)
                u->next = v;
            else if (v->size > u->next->size)
                u->next = v;

            u->children.push_back(v);
        }
    }  // foreach in G[u->key]
}

static void make_tree(int root) {
    memset(marked, false, sizeof(marked));
    marked[root] = true;
    nodes[root]->depth = 1;
    nodes[root]->father = NULL;
    make_tree(nodes[root]);
}

static int id_count;
static void split_tree(Node *x) {
    if (x->next) {
        x->next->id = id_count++;
        x->next->top = x->top;

        split_tree(x->next);
    }

    for (auto v : x->children) {
        if (v != x->next) {
            v->id = id_count++;
            v->top = v;

            split_tree(v);
        }
    }  // foreach in x->children
}

static void split_tree(int root) {
    id_count = 1;
    nodes[root]->id = 0;
    nodes[root]->top = nodes[root];
    split_tree(nodes[root]);
}

static void print_tree(Node *x, stringstream &buffer) {
    buffer << x->key << "[";
    if (x->top == x) {
        buffer << "color=red ";
    }
    buffer << "];" << endl;

    for (auto v : x->children) {
        buffer << x->key << "--" << v->key << "[label=" << v->id << " ";

        if (v == x->next) {
            buffer << "style=bold color=red";
        }
        buffer << "];" << endl;
    }  // foreach in x->children

    for (auto v : x->children) {
        print_tree(v, buffer);
    }  // foreach in x->children
}

static void print_tree(int root) {
    stringstream buffer;

    buffer << "strict graph {" << endl;
    buffer << "node [shape=circle];" << endl;
    print_tree(nodes[root], buffer);
    buffer << "}" << endl;

    ofstream file("/tmp/split-tree.dot");
    file << buffer.str();
    file.close();
    system("dot /tmp/split-tree.dot -Tsvg > /tmp/split-tree.svg");
    system("eog /tmp/split-tree.svg");
}

int main() {
    puts("Reading...");
    read_graph();

    puts("Making tree...");
    make_tree(1);

    puts("Spliting...");
    split_tree(1);

    puts("Printing...");
    print_tree(1);

    return 0;
}  // function main
