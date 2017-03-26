#include "icc.h"

#define NMAX 100

static int n;
static int alen, blen;
static int a[NMAX + 10], b[NMAX + 10];

void process(int &u, int &v) {
    int xorsum = 0;
    for (int i = 0; (1 << i) <= n; i++) {
        alen = blen = 0;
        for (int u = 1; u <= n; u++) {
            if ((u >> i) & 1)
                a[alen++] = u;
            else
                b[blen++] = u;
        }

        if (query(alen, blen, a, b))
            xorsum |= 1 << i;
    }

    int x = 0;
    while (!((xorsum >> x) & 1)) {
        x++;
    }

    v |= 1 << x;  // assume v[x] == 1
    for (int i = 0; (1 << i) <= n; i++) {
        if (x == i)
            continue;
        if ((xorsum >> i) & 1) {
            alen = blen = 0;
            for (int u = 1; u <= n; u++) {
                if (((u >> i) & 1) == 0 && ((u >> x) & 1) == 0)
                    a[alen++] = u;
                else if (((u >> i) & 1) && ((u >> x) & 1))
                    b[blen++] = u;
            }

            if (query(alen, blen, a, b))
                v |= 1 << i;
            else
                u |= 1 << i;
        } else {
            alen = blen = 0;
            for (int u = 1; u <= n; u++) {
                if (((u >> i) & 1) && ((u >> x) & 1) == 0)
                    a[alen++] = u;
                else if (((u >> i) & 1) && ((u >> x) & 1))
                    b[blen++] = u;
            }

            if (query(alen, blen, a, b)) {
                u |= 1 << i;
                v |= 1 << i;
            }
        }
    }
}

void run(int _n) {
    n = _n;
    for (int _t = 0; _t < n - 1; _t++) {
        int u = 0, v = 0;
        process(u, v);
        setRoad(u, v);
    }
}
