#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define KIND_NUMBER 3
#define NMAX 50000

static int n, k;
static int cnt;
static int mcnt;
static int father[NMAX + 10];
static int nxt[NMAX + 10];
static int set[NMAX + 10];

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }  // for
}

inline int find_set(int x) {
    if (set[x] != x)
        set[x] = find_set(set[x]);

    return set[x];
}

inline void union_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);

    set[a] = b;
}

inline void initialize() {
    cin >> n >> k;

    cnt = 0;
    mcnt = 0;
    make_set();

    memset(nxt, 0, sizeof(nxt));
    memset(father, 0, sizeof(father));
    nxt[0] = father[0] = 0;
}

inline void quit() {
    cout << cnt;
}

inline int get_node(int x, int index) {
    for (int i = 0; i < index; i++) {
        x = nxt[x];
    }  // for

    return x;
}

inline int get_length(int x) {
    int len = -1;

    int p = nxt[x];
    while (!(p == x or p == 0)) {
        p = nxt[p];
        len++;
    }  // while

    return len + 1;
}

int main() {
    ios::sync_with_stdio(false);
    initialize();

    for (int i = 1; i <= k; i++) {
        bool flag = true;
        int c, x, y;
        cin >> c >> x >> y;

        if ((c == 2 and x == y) or (x < 1 or x > n or y < 1 or y > n)) {
            flag = false;
        } else {
            x = find_set(x);
            y = find_set(y);

            switch (c) {
                case 1:
                    if (x != y) {
                        int p = nxt[x];
                        while (p != x and p != 0) {
                            flag = flag and p != y;
                            p = nxt[p];
                        }  // while

                        if (flag) {
                            union_set(x, y);
                        }
                    }
                    break;
                case 2:
                    if (nxt[x] != y) {
                        if (nxt[nxt[x]] == y) {
                            flag = false;
                            break;
                        }

                        // 合并
                        int a = x;
                        int b = y;
                        while (!(a == x or a == 0)) {
                            if (father[b] != 0) {
                                union_set(father[b], a);
                            }
                        }  // while

                        if (get_length(x) == 2) {
                            nxt[nxt[x]] = x;
                            father[x] = nxt[x];
                        } else if (get_length(father[x]) == 2) {
                            nxt[y] = father[x];
                            father[father[x]] = y;
                        }

                        nxt[x] = y;
                        father[y] = x;
                    }
                    break;
            }  // switch to c
        }

        if (!flag) {
            cnt++;
            cout << i << ": False" << endl;
        } else {
            cout << i << ": True" << endl;
        }
    }  // for

    quit();
    return 0;
}  // function main
