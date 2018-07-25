#include <cstdio>
#include <cstring>

#include <map>
#include <stack>
#include <iterator>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef map<int, int> VersionRecorder;

static int n;

static VersionRecorder set[NMAX + 10];
static VersionRecorder size[NMAX + 10];

inline int make_set() {
    for (int i = 1; i <= n; i++) {
        set[i][0] = i;
        size[i][0] = 1;
    }

    return 0;
}

inline int query(int x, int t, VersionRecorder *arr) {
    auto iter = arr[x].upper_bound(t);

    if (iter == arr[x].end())
        return arr[x].rbegin()->second;
    else
        return prev(iter)->second;
}

inline void modify(int x, int v, int t, VersionRecorder *arr) {
    arr[x][t] = v;
}

inline int find_set(int x, int t) {
    int v = query(x, t, set);
    while (x != v) {
        x = v;
        v = query(x, t, set);
    }

    return v;
}

inline int union_set(int x, int y, int t) {
    t++;
    x = find_set(x, t);
    y = find_set(y, t);

    if (x != y) {
        int xsize = query(x, t, size);
        int ysize = query(y, t, size);
        if (xsize < ysize) {
            modify(x, y, t, set);
            modify(y, xsize + ysize, t, size);
        } else {
            modify(y, x, t, set);
            modify(x, xsize + ysize, t, size);
        }
    }

    return t;
}

int main() {
    int q;
    scanf("%d%d", &n, &q);
    char command[100];

    stack<int> versions;
    versions.push(make_set());

    while (q--) {
        scanf("%s", command);

        if (strcmp(command, "Return") == 0) {
            versions.pop();
        } else if (strcmp(command, "Link") == 0) {
            int x, y;
            scanf("%d%d", &x, &y);

            versions.push(union_set(x, y, versions.top()));
        } else if (strcmp(command, "IsConnect") == 0) {
            int x, y;
            scanf("%d%d", &x, &y);
            
            x = find_set(x, versions.top());
            y = find_set(y, versions.top());

            puts(x == y ? "YES" : "NO");
        } else if (strcmp(command, "Size") == 0) {
            int x;
            scanf("%d", &x);

            int ver = versions.top();
            printf("%d\n", query(find_set(x, ver), ver, size));
        }
    }

    return 0;
}
