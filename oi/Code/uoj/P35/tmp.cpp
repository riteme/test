// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define SIGMA 27
#define EOFCHAR 0

struct Node {
    struct Edge {
        Edge(int l, int r, Node *nxt)
            : left(l), right(r), next(nxt) {}

        int left, right;
        Node *next;

        int length() {
            return right - left + 1;
        }
    };

    Node() : suffix_link(NULL) {
        memset(trans, 0, sizeof(trans));
    }

    Node *suffix_link;
    Edge *trans[SIGMA];
};

typedef Node::Edge Edge;

static int n;
static char str[NMAX + 10];
static Node *root;

void append(char c) {
    static Node *active = root;
    static char dir = -1;
    static int cur = 0, len = 0, tail = 0;

    cur++;
    tail++;
    Node *last = NULL;
    while (cur) {
        if (cur <= len) {
            len = cur - 1;
            dir = len ? str[tail - len - 1] : -1;
        }

        while (dir >= 0 && active->trans[dir]->length() <= len) {
            len -= active->trans[dir]->length();
            active = active->trans[dir]->next;
            dir = len ? str[tail - len - 1] : -1;
        }

        if ((dir >= 0 && c == str[active->trans[dir]->left + len]) ||
            (dir < 0  && active->trans[c])) {
            if (dir < 0)
                dir = c;
            len++;

            if (last)
                last->suffix_link = active;

            break;
        }

        Node *x;
        if (dir >= 0) {
            Edge *t = active->trans[dir];
            x = new Node;
            x->trans[str[t->left + len]] =
                new Edge(t->left + len, t->right, t->next);
            x->trans[c] = new Edge(tail - 1, n, new Node);
            t->right = t->left + len - 1;
            t->next = x;
        } else {
            active->trans[c] = new Edge(tail - 1, n, new Node);
            x = active;
        }

        if (last)
            last->suffix_link = x;
        last = x;

        active = active->suffix_link ? active->suffix_link : root;
        cur--;
    }
}

void dfs(Node *u, int depth, int &pos, int *arr) {
    bool has_child = false;
    for (char c = 0; c < SIGMA; c++) {
        Edge *t = u->trans[c];

        if (!t)
            continue;

        has_child = true;
        dfs(t->next, depth + t->length(), pos, arr);
    }

    if (!has_child) {
        arr[pos++] = n - depth + 2;
    }
}

static int pos;
static int sa[NMAX + 10];
static int rnk[NMAX + 10];
static int lcp[NMAX + 10];

void compute_lcp(int length, int *SA) {
    int j = 0;
    for (int i = 0; i <= length; i++) {
        if (rnk[i] == 0)
            continue;
        j--;
        if (j < 0)
            j = 0;
        while (str[SA[rnk[i]] + j - 1] == str[SA[rnk[i] - 1] + j - 1])
            j++;
        lcp[rnk[i]] = j;
    }  // for
}

int main() {
    scanf("%s", str);
    n = strlen(str);
    root = new Node;

    for (size_t i = 0; str[i]; i++) {
        str[i] -= 'a' - 1;
        append(str[i]);
    }
    str[n] = EOFCHAR;
    append(EOFCHAR);

    dfs(root, 0, pos, sa);

    for (int i = 1; i <= n; i++) {
        printf("%d ", sa[i]);
    }

    //sa[0] = 0;

    for (int i = 0; i <= n; i++) {
        rnk[sa[i]] = i;
    }  // for

    compute_lcp(n, sa);

    printf("\n");
    for (int i = 2; i <= n; i++) {
        printf("%d ", lcp[i]);
    }

    printf("\n");

    return 0;
}
