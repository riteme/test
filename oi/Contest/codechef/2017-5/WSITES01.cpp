#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000

struct Node {
    Node() : mark(false), has(false) {
        memset(go, 0, sizeof(go));
    }

    bool mark;
    bool has;
    Node *go[26];
};

void insert(Node *x, char *s, bool m) {
    if (s[0]) {
        int c = s[0] - 'a';
        if (!x->go[c])
            x->go[c] = new Node;
        insert(x->go[c], s + 1, m);
    } else
        x->has |= !m;

    x->mark |= m;
}

static bool ans;

int cnt(Node *x) {
    if (!x)
        return 0;
    if (x->mark && x->has)
        ans = true;
    if (!x->mark)
        return 1;

    int ret = 0;
    for (int c = 0; c < 26; c++) {
        ret += cnt(x->go[c]);
    }

    return ret;
}

static char str[NMAX + 10];

void print(Node *x, int pos) {
    if (!x)
        return;
    if (!x->mark) {
        str[pos] = 0;
        printf("%s\n", str);
    } else {
        for (int c = 0; c < 26; c++) {
            str[pos] = c + 'a';
            print(x->go[c], pos + 1);
        }
    }
}

int main() {
    Node *root = new Node;
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        char sign = getchar();
        while (sign != '+' && sign != '-')
            sign = getchar();
        scanf("%s", str);
        insert(root, str, sign == '+');
    }

    int c = cnt(root);
    if (ans)
        puts("-1");
    else {
        printf("%d\n", c);
        print(root, 0);
    }

    return 0;
}
