#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define IDMAX 1000000001

struct Inequality {
    int a, b;
};  // struct Inequality

static int n;
static int idcnt;
static unordered_map<int, int> hashtable;
static int s[NMAX * 2 + 10];

inline int hashing(int x) {
    if (!hashtable.count(x))
        hashtable[x] = idcnt++;
    return hashtable[x];
}

inline void make_set() {
    for (int i = 1; i <= NMAX * 2; i++) {
        s[i] = i;
    }  // for
}

inline int find_set(int x) {
    return x == s[x] ? x : s[x] = find_set(s[x]);
}

static void initialize() {
    scanf("%d", &n);
    idcnt = 1;
    hashtable.clear();
    make_set();
}

static vector<Inequality> inequ;

int main() {
    int t;
    scanf("%d", &t);

    while (t > 0) {
        initialize();
        inequ.clear();

        for (int _cnt = 0; _cnt < n; _cnt++) {
            int x, y, type;
            scanf("%d%d%d", &x, &y, &type);

            if (type == 1)
                s[find_set(hashing(x))] = find_set(hashing(y));
            else
                inequ.push_back({ x, y });
        }  // for

        for (size_t i = 0; i < inequ.size(); i++) {
            Inequality p = inequ[i];
            if (find_set(hashing(p.a)) == find_set(hashing(p.b))) {
                puts("NO");
                goto end_of_while;
            }
        }  // for
        puts("YES");

    end_of_while:
        t--;
    }  // while

    return 0;
}  // function main
