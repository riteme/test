#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define BUFFERSIZE 6000000

struct Node {
    Node() : lastpos(0), maxlen(0) {
        memset(next, 0, sizeof(next));
    }

    int lastpos;
    int maxlen;
    Node *next[3];
};

static Node *insert(Node *x, int pos, const char *str) {
    if (str[pos] == '\0')
        return x;

    int code = str[pos] - 'a';
    if (!x->next[code])
        x->next[code] = new Node;

    return insert(x->next[code], pos + 1, str);
}

static void update(Node *x, int id, int pos, const char *str) {
    if (!x)
        return;

    x->maxlen = max(x->maxlen, id - x->lastpos - 1);
    x->lastpos = id;

    if (str[pos] == '\0')
        return;

    int code = str[pos] - 'a';
    update(x->next[code], id, pos + 1, str);
}

static int n, m;
static int pos[NMAX + 10];
static char querys[BUFFERSIZE];
static char buffer[BUFFERSIZE];
static Node *root;
static Node *ref[NMAX + 10];

int main() {
    freopen("trie.in", "r", stdin);
    freopen("trie.out", "w", stdout);
    scanf("%d%d", &n, &m);

    pos[1] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%s", querys + pos[i]);
        pos[i + 1] = pos[i] + strlen(querys + pos[i]) + 1;
    }

    root = new Node;
    for (int i = 1; i <= m; i++) {
        scanf("%s", buffer);

        ref[i] = insert(root, 0, buffer);
    }

    for (int i = 1; i <= n; i++)
        update(root, i, pos[i], querys);

    for (int i = 1; i <= m; i++)
        printf("%d\n", max(n - ref[i]->lastpos, ref[i]->maxlen));

    fclose(stdin);
    fclose(stdout);
    return 0;
}
