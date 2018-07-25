#include <cstdio>

#include <map>

using namespace std;

typedef pair<int, int> Key;

static map<Key, bool> val;

bool query(int x, int y) {
    if (val.count(Key(x, y)))
        return val[Key(x, y)];
    printf("1 %d %d\n", x, y);
    fflush(stdout);
    static char buf[32];
    scanf("%s", buf);
    val[Key(x, y)] = buf[0] == 'T';
    return buf[0] == 'T';
}

static int n, k;

int brute(int l, int r) {
    for (int i = l; i <= r; i++) {
        bool lans = i == 1 ? true : query(i, i - 1);
        bool rans = i == n ? true : query(i, i + 1);
        
        if (lans && rans)
            return i;
    }

    return 0;
}

int search(int l, int r) {
    if (l > r)
        return 0;

    while (l < r) {
        int m = (l + r) / 2;

        if (query(m, m + 1))
            r = m;
        else
            l = m + 1;
    }

    return l;
}

int main() {
    scanf("%d%d", &n, &k);

    int x = search(1, n);
    int y = search(1, x - 1);
    if (!y || !query(y, x))
        y = search(x + 1, n);
    printf("2 %d %d\n", x, y);
    return 0;
}
