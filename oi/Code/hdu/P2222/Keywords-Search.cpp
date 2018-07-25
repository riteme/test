#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 10000
#define CMAX 26

struct Node {
    int count;
    Node *children[CMAX];
    Node *fail;
};  // struct Node

#define MEMORYSIZE 600000
static unsigned memcnt;
static Node memory[MEMORYSIZE];

inline void refresh_memory() {
    memcnt = 0;
}

inline Node *allocate() {
    memcnt++;

    memset(memory[memcnt].children, NULL, sizeof(memory[memcnt].children));
    memory[memcnt].count = 0;
    memory[memcnt].fail = NULL;

    return &memory[memcnt];
}

static Node *trie;

static void insert(const char *buffer) {
    Node *current = trie;
    for (unsigned pos = 0; buffer[pos] != '\0'; pos++) {
        unsigned i = buffer[pos] - 'a';
        if (!current->children[i])
            current->children[i] = allocate();

        current = current->children[i];
    }  // for

    current->count++;
}

static void build_automaton() {
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
                do {
                    if (y->children[i]) {
                        v->fail = y->children[i];
                        break;
                    }
                    y = y->fail;
                } while (y != trie);  // do ... while

                if (v->fail == NULL)
                    v->fail = trie;

                q.push(v);
            }
        }
    }  // while
}

#define BUFFERSIZE 1000000

static char target[BUFFERSIZE + 10];

int main() {
    int t;
    scanf("%d", &t);

    for (int _cnt = 0; _cnt < t; _cnt++) {
        refresh_memory();
        trie = allocate();

        int n;
        char buffer[100];
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", buffer);

            insert(buffer);
        }  // for

        build_automaton();

        scanf("%s", target);
        int answer = 0;
        Node *x = trie;

        for (unsigned pos = 0; target[pos] != '\0'; pos++) {
            unsigned i = target[pos] - 'a';

            while (x != trie && x->children[i] == NULL)
                x = x->fail;

            if (x->children[i])
                x = x->children[i];

            Node *y = x;
            while (y->count > 0) {
                answer += y->count;
                y->count = 0;
                y = y->fail;
            }
        }  // for

        printf("%d\n", answer);
    }  // for

    return 0;
}  // function main
