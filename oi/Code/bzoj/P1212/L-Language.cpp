#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

#define NAMX 20
#define BUFFERSIZE 20
#define MESSAGEMAX 1000000
#define CMAX 26

struct Node {
    Node() : mark(false), depth(0), fail(NULL) {
        memset(children, 0, sizeof(children));
    }

    char c;
    bool mark;
    int depth;
    Node *children[CMAX];
    Node *fail;
};  // struct Node

static Node *trie;

static void insert(const char *buffer) {
    Node *x = trie;
    for (unsigned pos = 0; buffer[pos] != '\0'; pos++) {
        unsigned i = buffer[pos] - 'a';

        if (!x->children[i]) {
            x->children[i] = new Node;
            x->children[i]->depth = x->depth + 1;
            x->children[i]->c = buffer[pos];
        }

        x = x->children[i];
    }  // for

    x->mark = true;
}

static void build_automaton() {
    queue<Node *> q;
    trie->fail = trie;

    for (unsigned i = 0; i < CMAX; i++) {
        if (trie->children[i]) {
            trie->children[i]->fail = trie;
            q.push(trie->children[i]);
        }
    }  // for

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
                }  // while

                if (!v->fail) {
                    if (trie->children[i]) {
                        v->fail = trie->children[i];
                    } else {
                        v->fail = trie;
                    }
                }

                q.push(v);
            }
        }  // for
    }      // while
}

static int n, m;

static void initialize() {
    scanf("%d%d", &n, &m);

    trie = new Node;
    char buffer[BUFFERSIZE];
    for (int i = 1; i <= n; i++) {
        scanf("%s", buffer);
        insert(buffer);
    }  // for

    build_automaton();
}

static char target[MESSAGEMAX];
static bool f[MESSAGEMAX];

int main() {
    // freopen("language.in", "r", stdin);
    // freopen("language.out", "w", stdout);
    initialize();

    for (int _cnt = 0; _cnt < m; _cnt++) {
        scanf("%s", target);

        int l = strlen(target);
        memset(f, 0, sizeof(f));
        f[0] = true;

        Node *x = trie;
        for (int pos = 0; pos < l; pos++) {
            int i = target[pos] - 'a';

            while (x != trie && !x->children[i]) {
                x = x->fail;
            }  // while

            if (x->children[i])
                x = x->children[i];

            Node *y = x;
            while (y != trie) {
                if (y->mark && f[pos + 1 - y->depth]) {
                    f[pos + 1] = true;
                }
                y = y->fail;
            }  // while
        }      // for

        int matched = 0;
        for (int pos = 1; pos <= l; pos++) {
            if (f[pos]) {
                matched = pos;
            }
        }  // for

        printf("%d\n", matched);
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
