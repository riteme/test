#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 =  long long;
using vi = vector<int>;

constexpr int LOGA = 31;

struct Node {
    Node() {
        memset(ch, 0, sizeof(ch));
    }

    vi seq;
    Node *ch[2];
};

int n;
Node *tr = new Node;

void insert(Node *x, int v, int i, int d) {
    x->seq.push_back(i);
    if (d >= LOGA)
        return;

    int b = (v >> (LOGA - d - 1)) & 1;
    if (!x->ch[b])
        x->ch[b] = new Node;
    insert(x->ch[b], v, i, d + 1);
}

i64 cnt[LOGA][2];

void solve(Node *x, int d) {
    if (d >= LOGA || !x)
        return;

    solve(x->ch[0], d + 1);
    solve(x->ch[1], d + 1);

    if (!x->ch[0] || !x->ch[1])
        return;

    vi &a = x->ch[0]->seq;
    vi &b = x->ch[1]->seq;
    if (a.size() < b.size()) {
        for (int i : a) {
            auto lt = lower_bound(b.begin(), b.end(), i);
            auto rt = upper_bound(b.begin(), b.end(), i);
            cnt[d][0] += lt - b.begin();
            cnt[d][1] += b.end() - rt;
        }
    } else {
        for (int j : b) {
            auto lt = lower_bound(a.begin(), a.end(), j);
            auto rt = upper_bound(a.begin(), a.end(), j);
            cnt[d][0] += a.end() - rt;
            cnt[d][1] += lt - a.begin();
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        insert(tr, v, i, 0);
    }
    solve(tr, 0);

    i64 mask = 0, ans = 0;
    for (int i = 0; i < LOGA; i++) {
        ans += min(cnt[i][0], cnt[i][1]);
        if (cnt[i][1] < cnt[i][0])
            mask |= 1LL << (LOGA - i - 1);
    }

    printf("%lld %lld\n", ans, mask);
    return 0;
}