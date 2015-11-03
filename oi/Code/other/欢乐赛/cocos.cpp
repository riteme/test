#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ntype;

#define TYPE_SUM 0
#define TYPE_MAX 1

struct Node {
    int left;
    int right;
    int type;
    int nodecnt;
    //	ntype cocos;
};

static int *father;
static int *type;
static ntype *cocos;
static Node *tree;
static int *cnt;

bool Compare(const ntype a, const ntype b) { return a > b; }

int main() {
    freopen("cocos.in", "r", stdin);
    freopen("cocos.out", "w", stdout);

    int n;
    scanf("%d", &n);

    father = new int[n - 2 + 1];
    type = new int[n - 1 + 1];
    cocos = new ntype[n + 1];
    tree = new Node[n - 1 + 1];
    cnt = new int[n - 1 + 1];

    for (int i = 1; i <= n - 2; i++) { scanf("%d", &father[i]); }
    for (int i = 1; i <= n - 1; i++) {
        scanf("%d", &type[i]);

        Node tmp;
        tmp.left = 0;
        tmp.right = 0;
        tmp.nodecnt = 0;
        tmp.type = type[i];

        tree[i] = tmp;
    }
    for (int i = 1; i <= n; i++) { scanf("%lld", &cocos[i]); }

    if (n == 1) {
        printf("%lld", cocos[1]);
        return 0;
    }

    std::sort(cocos + 1, cocos + n + 1, Compare);

    for (int i = 1; i <= n - 2; i++) {
        Node *fa = &tree[father[i]];

        if (fa->left == 0) { fa->left = i + 1; } else {
            fa->right = i + 1;
        }

        fa->nodecnt++;
    }

    cnt[0] = 1;
    for (int i = n - 1; i >= 1; i--) {
        if (tree[i].nodecnt == 0)
            cnt[i] = tree[i].type == TYPE_SUM ? 2 : 1;
        else
            cnt[i] = tree[i].type == TYPE_SUM
                         ? cnt[tree[i].left] + cnt[tree[i].right]
                         : std::max(cnt[tree[i].left], cnt[tree[i].right]);
    }  // for

    ntype answer = 0;
    for (int i = 1; i <= cnt[1]; i++) { answer += cocos[i]; }  // for

    printf("%lld", answer);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
