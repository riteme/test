#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

static int n;

#define CMAX 26
#define BUFFERSIZE 50
#define NMAX 30

struct Node {
    Node() : count(0), id(0), fail(NULL) {
        memset(children, NULL, sizeof(children));
    }

    char c;
    int count;
    int id;
    Node *children[CMAX];
    Node *fail;
};  // struct Node

static Node *trie;
static int ansid;
static int answer[NMAX + 10];
static char buffer[NMAX + 10][BUFFERSIZE];

static void insert(const char *buffer) {
    Node *current = trie;
    for (unsigned pos = 0; buffer[pos] != '\0'; pos++) {
        unsigned i = buffer[pos] - 'a';
        if (!current->children[i]) {
            current->children[i] = new Node;
            current->children[i]->c = buffer[pos];
        }

        current = current->children[i];
    }  // for

    current->id = ansid;
}

static void construct_automaton() {
    trie->fail = trie;
    queue<Node *> q;

    for (unsigned i = 0; i < CMAX; i++) {
        if (trie->children[i]) {
            trie->children[i]->fail = trie;
            q.push(trie->children[i]);
        }
    }

    while (!q.empty()) {
        Node *x = q.front();
        q.pop();

        for (unsigned i = 0; i < CMAX; i++) {
            if (x->children[i]) {
                Node *v = x->children[i];
                Node *y = x->fail;
                while (y != trie) {
                    if (y->children[i]) {
                        v->fail = y->children[i];
                        break;
                    }
                    y = y->fail;
                }

                if (v->fail == NULL) {
                    if (trie->children[i])
                        v->fail = trie->children[i];
                    else
                        v->fail = trie;
                }

                q.push(v);
            }
        }
    }  // while
}

static void initialize() {
    scanf("%d", &n);

    trie = new Node;

    for (int i = 0; i < n; i++) {
        scanf("%s", &buffer[++ansid][0]);

        insert(&buffer[ansid][0]);
    }  // for

    construct_automaton();
}

static void dfs(Node *x) {
    if (x->id > 0) {
        answer[x->id] = x->count;
    }

    for (unsigned i = 0; i < CMAX; i++) {
        if (x->children[i])
            dfs(x->children[i]);
    }  // for
}

int main() {
    freopen("ACautomata.in", "r", stdin);
    freopen("ACautomata.out", "w", stdout);
    initialize();

    char c = getchar();
    while (c < 'a' || 'z' < c)
        c = getchar();

    Node *x = trie;
    while ('a' <= c && c <= 'z') {
        unsigned i = c - 'a';

        while (x != trie && !x->children[i])
            x = x->fail;

        if (x->children[i])
            x = x->children[i];

        Node *y = x;
        while (y != trie) {
            if (y->id > 0)
                y->count++;
            y = y->fail;
        }

        c = getchar();
    }

    dfs(trie);

    for (int i = 1; i <= ansid; i++) {
        printf("%s %d\n", &buffer[i][0], answer[i]);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
