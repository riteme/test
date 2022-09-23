#include <cassert>
#include <cstring>

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

using i64 = long long;
using u8 = unsigned char;

constexpr i64 INF = 10000000000;

struct Fn {
    u8 a[8][16];

    Fn() {
        for (int i = 0; i < 8; i++) {
            for (int x = 0; x < 16; x++) {
                a[i][x] = x;
            }
        }
    }

    u8 &operator()(int i, int x) {
        return a[i][x];
    }

    u8 operator()(int i, int x) const {
        return a[i][x];
    }

    Fn operator*(const Fn &b) const {
        Fn c;
        for (int i = 0; i < 8; i++) {
            for (int x = 0; x < 16; x++) {
                c(i, x) = a[i][b(i, x)];
            }
        }
        return c;
    }
};

Fn qpow(Fn f, i64 k) {
    Fn g;
    for ( ; k; k >>= 1) {
        if (k & 1)
            g = g * f;
        f = f * f;
    }
    return g;
}

int n, q;

string read_token() {
    if (n) {
        n--;
        string s;
        cin >> s;
        return s;
    }
    return "end";
}

int idx(const string &s) {
    return s[0] - 'a';
}

struct Node {
    i64 c;
    vector<Node *> child;
    Fn f1, fc, g, h;  // f full, g sibling, h first time
    i64 one, tot;

    Node() : c(0) {}
    Node(i64 _c) : c(_c) {
        while (true) {
            string s = read_token();
            if (s[0] == 'e')
                break;
            if (s[0] == 'r') {
                i64 m;
                cin >> m;
                child.push_back(new Node(m));
                continue;
            }

            auto v = new Node;
            child.push_back(v);
            string as, bs;
            cin >> as >> bs;
            if (s[0] == 'o' && s.length() == 2) {
                // or
                int a = idx(as);
                int b = idx(bs);
                for (int i = 0; i < 8; i++) {
                    for (int x = 0; x < 16; x++) {
                        v->f1(i, x) = x | (((x >> b) & 1) << a);
                    }
                }
            } else if (s[0] == 'o' && s.length() == 3) {
                // ori
                int a = idx(as);
                int imm = atoi(bs.c_str());
                for (int i = 0; i < 8; i++) {
                    for (int x = 0; x < 16; x++) {
                        v->f1(i, x) = x | (((imm >> i) & 1) << a);
                    }
                }
            } else if (s[0] == 'a' && s.length() == 3) {
                // and
                int a = idx(as);
                int b = idx(bs);
                for (int i = 0; i < 8; i++) {
                    for (int x = 0; x < 16; x++) {
                        v->f1(i, x) = x & (~(((x >> b) & 1) << a) ^ (1 << a));
                    }
                }
            } else if (s[0] == 'a' && s.length() == 4) {
                // andi
                int a = idx(as);
                int imm = atoi(bs.c_str());
                for (int i = 0; i < 8; i++) {
                    for (int x = 0; x < 16; x++) {
                        v->f1(i, x) = x & (~(((imm >> i) & 1) << a) ^ (1 << a));
                    }
                }
            } else if (s[0] == 'x' && s.length() == 3) {
                // xor
                int a = idx(as);
                int b = idx(bs);
                for (int i = 0; i < 8; i++) {
                    for (int x = 0; x < 16; x++) {
                        v->f1(i, x) = x ^ (((x >> b) & 1) << a);
                    }
                }
            } else {
                // xori
                int a = idx(as);
                int imm = atoi(bs.c_str());
                for (int i = 0; i < 8; i++) {
                    for (int x = 0; x < 16; x++) {
                        v->f1(i, x) = x ^ (((imm >> i) & 1) << a);
                    }
                }
            }

            v->fc = v->f1;
        }

        // compute f
        for (auto v : child) {
            f1 = v->fc * f1;
        }
        fc = qpow(f1, c);
    }
};

i64 fix(i64 x) {
    return x > INF ? INF : x;
}

void dfs(Node *u) {
    if (u->c == 0) {
        u->one = u->tot = 1;
        return;
    }

    Fn g, h = u->h;
    u->one = 0;
    for (auto v : u->child) {
        v->g = g;
        v->h = h;
        dfs(v);
        u->one = fix(u->one + v->tot);
        g = v->fc * g;
        h = v->fc * h;
    }
    u->tot = fix(u->one * u->c);
}

struct Context {
    int a, b, c, d;

    void apply(const Fn &f) {
        Context n = {};
        for (int i = 0; i < 8; i++) {
            int x = ((a >> i) & 1) << 0
                  | ((b >> i) & 1) << 1
                  | ((c >> i) & 1) << 2
                  | ((d >> i) & 1) << 3;
            int y = f(i, x);
            n.a |= ((y >> 0) & 1) << i;
            n.b |= ((y >> 1) & 1) << i;
            n.c |= ((y >> 2) & 1) << i;
            n.d |= ((y >> 3) & 1) << i;
        }
        memcpy(this, &n, sizeof(n));
    }
};

void solve2(Node *u, int k, Context &ctx) {
    if (u->c == 0) {
        assert(k == 1);
        ctx.apply(u->fc);
        return;
    }

    i64 c = k / u->one;
    if (c > 0) {
        Fn f = qpow(u->f1, c);
        ctx.apply(f);
        k %= u->one;
    }
    if (k == 0)
        return;

    i64 sum = 0;
    for (auto v : u->child) {
        if (sum + v->tot >= k) {
            ctx.apply(v->g);
            solve2(v, k - sum, ctx);
            return;
        }
        sum = fix(sum + v->tot);
    }
}

void solve1(Node *u, int k, Context &ctx) {
    if (u->one <= k) {
        ctx.apply(u->h);
        solve2(u, k, ctx);
        return;
    }

    i64 sum = 0;
    for (auto v : u->child) {
        if (sum + v->tot >= k) {
            solve1(v, k - sum, ctx);
            return;
        }
        sum = fix(sum + v->tot);
    }
    abort();
}

int main() {
    ios::sync_with_stdio(false);

    cin >> n >> q;
    auto ast = new Node(1);
    dfs(ast);

    while (q--) {
        int k;
        Context ctx;
        cin >> k >> ctx.a >> ctx.b >> ctx.c >> ctx.d;
        solve1(ast, k, ctx);
        cout << ctx.a << " " << ctx.b << " " << ctx.c << " " << ctx.d << "\n";
    }
    cout << endl;
    return 0;
}
