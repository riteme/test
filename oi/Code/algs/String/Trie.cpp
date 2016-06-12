#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

#define CMAX 256

struct Node {
    Node() : c('^'), id(0) {
        memset(next, 0, sizeof(next));
    }

    char c;
    int id;
    Node *next[CMAX];
};  // struct Node

static int id = 1;
static Node *trie;

static void insert(const char *buffer) {
    Node *x = trie;
    for (unsigned pos = 0; buffer[pos] != '\0'; pos++) {
        unsigned i = buffer[pos];

        if (!x->next[i]) {
            x->next[i] = new Node;
            x->next[i]->c = buffer[pos];
            x->next[i]->id = id++;
        }

        x = x->next[i];
    }  // for
}

static void print(Node *x, stringstream &buffer) {
    if (!x)
        return;

    buffer << x->id << "[label=\"" << x->c << "\"];";
    for (unsigned i = 0; i < CMAX; i++) {
        if (x->next[i]) {
            buffer << x->id << "->" << x->next[i]->id << "[rank=0];";
            print(x->next[i], buffer);
        }
    }  // for
}

static void show(Node *x) {
    stringstream buffer;

    buffer << "digraph {node[shape=circle];";
    print(x, buffer);
    buffer << "}";

    ofstream file("/tmp/trie.tmp.dot");
    // printf("%s", buffer.str().c_str());
    file << buffer.str();
    file.close();
    system("showdot /tmp/trie.tmp.dot");
}

static char buffer[10000];
int main() {
    scanf("%s", buffer);
    int l = strlen(buffer);
    buffer[l] = '#';
    buffer[l + 1] = 0;

    trie = new Node;
    for (int i = 0; i <= l; i++) {
        insert(buffer + i);
    }  // for

    show(trie);

    return 0;
}  // function main
