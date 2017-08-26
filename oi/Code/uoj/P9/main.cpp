#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100

struct Node {
    Node() {
        memset(go, 0, sizeof(go));
    }

    Node *go[10];
};

static int n;
static Node *root;
static char pre[NMAX + 10], suf[NMAX + 10];
static char buf[NMAX + 10];
static int tmp[NMAX + 10];

void insert() {
    Node *x = root;
    for (int i = 0; i < NMAX; i++) {
        int c = tmp[i];
        if (!x->go[c])
            x->go[c] = new Node;
        x = x->go[c];
    }
}

static int stk[NMAX + 10];

void print(Node *x, int pos) {
    if (!x)
        return;
    if (pos == NMAX) {
        printf("%s", pre);
        int i = 0;
        for(; !stk[i]; i++);
        for (; i < pos; i++) {
            putchar(stk[i] + '0');
        }
        printf("%s\n", suf);
    }

    for (int c = 0; c < 10; c++) {
        stk[pos] = c;
        print(x->go[c], pos + 1);
    }
}

int main() {
    scanf("%d", &n);
    root = new Node;

    while (n--) {
        scanf("%s", buf);
        int i = strlen(buf) - 1;
        int len = 0;
        while (buf[i] != '.') {
            i--;
            len++;
        }
        memcpy(suf, buf + i, len + 1);
        i--;
        int pos = NMAX - 1;
        memset(tmp, 0, sizeof(tmp));
        for (; i >= 0 && isdigit(buf[i]); i--) {
            tmp[pos--] = buf[i] - '0';
        }
        insert();

        if (!n)
            memcpy(pre, buf, i + 1);
    }

    print(root, 0);
    return 0;
}
