#include <cstdio>
#include <vector>

struct Edge {
    int u, v;
};

using namespace std;

vector<Edge> es;

void add(int u, int v) {
    es.push_back({u, v});
}

void okay() {
    printf("%zu\n", es.size());
    for (auto e : es) {
        printf("%d %d\n", e.u, e.v);
    }
    es.clear();
}

void fail() {
    puts("-1");
    es.clear();
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d%d", &n, &k);
        int m = n - k;
        if (n == 4 && k == 0) {
            add(1, 2);
            add(2, 3);
            add(3, 4);
            add(4, 1);
            okay();
        } else if (n == 5 && k == 0) {
            add(1, 2);
            add(2, 3);
            add(3, 4);
            add(4, 5);
            add(5, 1);
            okay();
        } else if (n == 6 && k == 0) {
            add(1, 2);
            add(2, 3);
            add(3, 4);
            add(5, 1);
            add(5, 4);
            add(6, 1);
            add(6, 4);
            okay();
        } else if (m == 2) {
            fail();
        } else if (m > 0) {
            for (int i = 1; i < n; i++) {
                add(i, n);
            }
            for (int i = k + 1; i + 1 < n; i += 2) {
                add(i, i + 1);
            }
            if (m % 2 == 0)  // m >= 4
                add(n - 1, n - 2);
            okay();
        } else {
            fail();
        }
    }

    return 0;
}
