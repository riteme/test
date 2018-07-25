#include <cstdio>

#include <map>
#include <vector>
#include <iterator>

using namespace std;

#define NMAX 300000

typedef long long int64;

static int n, q;
static int ver;
static int64 answer[NMAX + 10];

struct Modification {
    int x;
    map<int, int> *target;
};

static map<int, int> set[NMAX + 10];
static map<int, int> size[NMAX + 10];
static vector<Modification> record[NMAX + 10];

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i][0] = i;
        size[i][0] = 1;
    }
}

inline int query(int x, int ver, map<int, int> *target) {
    auto iter = target[x].upper_bound(ver);

    if (iter == target[x].end())
        return target[x].rbegin()->second;
    else
        return prev(iter)->second;
}

inline void modify(int x, int v, int ver, map<int, int> *target) {
    target[x][ver] = v;

    record[ver].push_back({x, target});
}

inline int find_set(int x, int ver) {
    int v = query(x, ver, set);
    while (x != v) {
        x = v;
        v = query(x, ver, set);
    }

    return v;
}

inline void refresh(int ver) {
    for (auto &e : record[ver]) {
        auto iter = e.target[e.x].find(ver);

        if (iter != e.target[e.x].end())
            e.target[e.x].erase(iter);
    }

    record[ver].clear();
}

inline int direct_union_set(int x, int y, int ver) {
    if (x != y) {
        int xsize = query(x, ver, size);
        int ysize = query(y, ver, size);

        ver++;
        refresh(ver);

        if (xsize < ysize) {
            modify(x, y, ver, set);
            modify(y, xsize + ysize, ver, size);
        } else {
            modify(y, x, ver, set);
            modify(x, xsize + ysize, ver, size);
        }
    }

    return ver;
}

inline int union_set(int x, int y, int ver) {
    x = find_set(x, ver);
    y = find_set(y, ver);

    return direct_union_set(x, y, ver);
}

static char lastc;
static int x, y;
static int k;

int main() {
    // freopen("graph.in", "r", stdin);

    scanf("%d%d", &n, &q);
    char command[10];

    make_set();
    for (int i = 1; i <= q; i++) {
        scanf("%s", command);

        switch (command[0]) {
            case 'A': {
                scanf("%d%d", &x, &y);
                x = find_set(x, ver);
                y = find_set(y, ver);

                if (x != y) {
                    answer[ver + 1] = answer[ver] + i;
                    ver = direct_union_set(x, y, ver);
                } else {
                    answer[ver + 1] = answer[ver];
                    ver++;
                    refresh(ver);
                }
            } break;
            
            case 'D': {
                scanf("%d", &k);
                ver -= k;
            } break;

            case 'R': {
                if (lastc == 'A')
                    ver--;
                else
                    ver += k;
            } break;
        }

        lastc = command[0];
        if (query(find_set(1, ver), ver, size) == n)
            printf("%lld\n", answer[ver]);
        else
            puts("0");
    }

    return 0;
}
