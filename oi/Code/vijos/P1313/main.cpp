// 金明的预算方案
// 泛化物品？

#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

typedef int ntype;

#define NDEBUG

#define NMAX 32000
#define MMAX 60
#define VMAX 10000
#define PMAX 5

struct Stuff {
    Stuff() : price(0), importance(0) {}

    ntype price;
    ntype importance;

    ntype value() const { return price * importance; }
};  // struct Stuff

struct StuffGroup {
    StuffGroup() : main_stuff(NULL), left(NULL), right(NULL) {}

    Stuff *main_stuff;
    Stuff *left;
    Stuff *right;
};  // struct Group

static ntype n, m;
static ntype group_count;
static Stuff stuffs[MMAX + 10];
static StuffGroup groups[MMAX + 10];
static ntype redirect[MMAX + 10];
static ntype f[NMAX + 10];

void initialize();
void output();

int main() {
    ios::sync_with_stdio(false);
    initialize();

    for (int i = 1; i <= group_count; i++) {
        StuffGroup &g = groups[i];

#ifndef NDEBUG
        cout << "LEFT: " << g.left << ", RIGHT: " << g.right << endl;
#endif  // IFNDEF NDEBUG

        for (int j = n; j >= g.main_stuff->price; j--) {
            // 只选取主件
            if (j >= g.main_stuff->price) {
                f[j] = max(f[j],
                           f[j - g.main_stuff->price] + g.main_stuff->value());
            }

            // 选取主件与左件
            if (g.left != NULL and j >= g.main_stuff->price + g.left->price) {
                f[j] = max(f[j],
                           f[j - (g.main_stuff->price + g.left->price)] +
                               g.main_stuff->value() + g.left->value());
            }

            // 选取主件与右件
            if (g.right != NULL and j >= g.main_stuff->price + g.right->price) {
                f[j] = max(f[j],
                           f[j - (g.main_stuff->price + g.right->price)] +
                               g.main_stuff->value() + g.right->value());
            }

            // 全部选取
            if (g.right != NULL and
                j >= g.main_stuff->price + g.left->price + g.right->price) {
                f[j] = max(f[j],
                           f[j - (g.main_stuff->price + g.left->price +
                                  g.right->price)] +
                               g.main_stuff->value() + g.left->value() +
                               g.right->value());
            }
        }  // for
    }      // for

    output();
    return 0;
}  // function main

void initialize() {
    group_count = 0;
    fill(&f[0], &f[n + 1], 0);
    fill(&redirect[0], &redirect[MMAX + 1], 0);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        ntype v, p, q;
        cin >> v >> p >> q;

        Stuff *s = &stuffs[i];
        s->price = v;
        s->importance = p;

        if (q == 0) {
            redirect[i] = ++group_count;
            groups[group_count].main_stuff = s;
        } else {
            StuffGroup &g = groups[redirect[q]];

            if (g.left == NULL)
                g.left = s;
            else
                g.right = s;
        }
    }  // for
}

void output() { cout << f[n]; }
