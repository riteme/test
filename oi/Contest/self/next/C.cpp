#include <cstdio>
#include <cctype>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define INPUT_BUFFERSIZE 65536
static size_t ipos = INPUT_BUFFERSIZE;
static char ibuffer[INPUT_BUFFERSIZE];

inline char _getchar() {
    if (ipos == INPUT_BUFFERSIZE) {
        ipos = 0;
        fread(ibuffer, 1, INPUT_BUFFERSIZE, stdin);
    }

    return ibuffer[ipos++];
}

inline char next_char() {
    char c = _getchar();

    while (!isalpha(c))
        c = _getchar();
    
    return c;
}

inline int readint() {
    int x = 0;
    char c = _getchar();

    while (!isdigit(c))
        c = _getchar();
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 1000000
#define MMAX 1500000

enum CommandType {
    ADD,
    COPY,
    QUERY
};

struct Command {
    CommandType type;
    int ver;
    int a, b, c;
    int answer;
};

struct Node {
    Node ()
        : left(0), right(0) {}

    vector<Command *> ops;
    Node *left;
    Node *right;
};

static int n, m;
static Command commands[MMAX + 10];
static Node *root;
static Node *node[MMAX + 10];

static int fenwick[NMAX + 10];

inline int query(int r) {
    int answer = 0;

    for (; r; r -= r & (-r)) {
        answer += fenwick[r];
    }

    return answer;
}

inline void modify(int x, int v) {
    for (; x <= n; x += x & (-x)) {
        fenwick[x] += v;
    }
}

static void initialize() {
    // scanf("%d%d", &n, &m);
    n = readint();
    m = readint();

    node[1] = new Node;
    root = node[1];

    char command;
    int ver = 1;
    for (int i = 1; i <= m; i++) {
        // scanf("%s", command);
        command = next_char();

        Command &comm = commands[i];
        if (command == 'A') {
            // scanf("%d%d%d", &comm.a, &comm.b, &comm.c);
            comm.a = readint();
            comm.b = readint();
            comm.c = readint();

            comm.type = ADD;
            node[comm.a]->ops.push_back(&comm);
        } else if (command == 'C') {
            // scanf("%d", &comm.a);
            comm.a = readint();

            comm.type = COPY;
            comm.ver = ++ver;

            node[ver] = new Node;
            Node *newnode = new Node;
            node[comm.a]->left = node[ver];
            node[comm.a]->right = newnode;
            node[comm.a] = newnode;
        } else {
            // scanf("%d%d%d", &comm.a, &comm.b, &comm.c);
            comm.a = readint();
            comm.b = readint();
            comm.c = readint();

            comm.type = QUERY;
            node[comm.a]->ops.push_back(&comm);
        }
    }
}

static void answer_all(Node *x) {
    for (size_t i = 0; i < x->ops.size(); i++) {
        Command *comm = x->ops[i];

        if (comm->type == QUERY) {
            comm->answer = query(comm->c) - query(comm->b - 1);
        } else {
            modify(comm->b, comm->c);
        }
    }

    if (x->left)
        answer_all(x->left);
    if (x->right)
        answer_all(x->right);

    for (size_t i = 0; i < x->ops.size(); i++) {
        Command *comm = x->ops[i];

        if (comm->type == ADD) {
            modify(comm->b, -comm->c);
        }
    }
}

int main() {
    initialize();

    answer_all(root);

    for (int i = 1; i <= m; i++) {
        Command &comm = commands[i];

        if (comm.type == QUERY) {
            printf("%d\n", comm.answer);
        }
    }

    return 0;
}
