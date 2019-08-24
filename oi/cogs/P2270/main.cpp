#include <cstdio>
#include <cstring>

#include <algorithm>

#define NMAX 200000
#define SIGMA 28
#define EOFCHAR1 26
#define EOFCHAR2 27

typedef long long i64;

static int n1, n2;
static char s[NMAX * 2 + 10];

struct Node {
    struct Edge {
        Edge(int l, int r, Node *nxt) : left(l), right(r), next(nxt) {}

        int left, right;
        Node *next;

        int length() {
            return right - left + 1;
        }
    };  // struct Edge

    Node() : acnt(0), bcnt(0), suffix_link(NULL) {
        memset(trans, 0, sizeof(trans));
    }

    i64 acnt, bcnt;
    Node *suffix_link;
    Edge *trans[SIGMA];
};  // struct Node

typedef Node::Edge Edge;

static Node *root;
static int eoln;

void append(char c) {
    static Node *active = root;
    static char dir = -1;
    static int len = 0;
    static int cnt = 0;
    static int size = 0;

    size++, cnt++;
    Node *last = NULL;
    while (cnt) {
        if (cnt - 1 < len) {
            len = cnt - 1;
            dir = len ? s[size - len] : -1;
        }

        while (dir >= 0 && len >= active->trans[dir]->length()) {
            len -= active->trans[dir]->length();
            active = active->trans[dir]->next;
            dir = len ? s[size - len] : -1;
        }  // while

        if ((dir < 0 && active->trans[c]) ||
            (dir >= 0 && c == s[active->trans[dir]->left + len])) {
            if (dir < 0)
                dir = c;
            len++;
            if (last)
                last->suffix_link = active;
            break;
        }

        Node *x;
        if (dir < 0) {
            active->trans[c] = new Edge(size, eoln, new Node);
            x = active;
        } else {
            Edge *t = active->trans[dir];
            x = new Node;
            x->trans[c] = new Edge(size, eoln, new Node);
            x->trans[s[t->left + len]] =
                new Edge(t->left + len, t->right, t->next);
            t->right = t->left + len - 1;
            t->next = x;
        }

        if (last)
            last->suffix_link = x;
        last = x;
        if (active != root)
            active = active->suffix_link;
        cnt--;
    }  // while
}

void initialize() {
    scanf("%s", s + 1);
    n1 = strlen(s + 1);
    scanf("%s", s + n1 + 2);
    n2 = strlen(s + n1 + 2);

    root = new Node;
    eoln = n1 + 1;
    for (int i = 1; i <= n1; i++) {
        s[i] -= 'a';
        append(s[i]);
    }  // for
    s[n1 + 1] = EOFCHAR1;
    append(EOFCHAR1);

    eoln = n1 + n2 + 2;
    for (int i = n1 + 2; i <= n1 + n2 + 1; i++) {
        s[i] -= 'a';
        append(s[i]);
    }  // for
    s[n1 + n2 + 2] = EOFCHAR2;
    append(EOFCHAR2);
}

i64 dfs(Node *x, int len = 0) {
    i64 ret = 0;

    for (char c = 0; c < SIGMA; c++) {
        Edge *t = x->trans[c];

        if (!t)
            continue;

        if (t->left <= n1 + 1 && n1 + 1 <= t->right)
            x->acnt++;
        else if (t->left <= n1 + n2 + 2 && n1 + n2 + 2 <= t->right)
            x->bcnt++;
        else {
            ret += dfs(t->next, t->length());
            x->acnt += t->next->acnt;
            x->bcnt += t->next->bcnt;
        }
    }  // for

    return ret + len * (x->acnt && x->bcnt ? 1 : 0);
}

int main() {
    freopen("find2.in", "r", stdin);
    freopen("find2.out", "w", stdout);
    initialize();
    printf("%lld\n", dfs(root));

    return 0;
}  // function main
