#include <cstdio>
#include <algorithm>

using namespace std;

#define NMAX 5000

struct Interval {
    int s;
    int t;

    bool operator<(const Interval &lhs) const { return s < lhs.s; }
};

static int n;
static Interval intervals[NMAX + 10];
static int as, ae;
static int ls, le;
static int ns, ne;

void initialize();
void output();

inline int length_of(int s, int e) { return e - s; }

inline bool is_intersect(int os, int oe, int s, int e) { return s <= oe; }

inline void union_set(int &os, int &oe, int s, int e) {
    if (is_intersect(os, oe, s, e)) { oe = max(oe, e); } else {
        if (length_of(os, oe) < length_of(s, e)) {
            os = s;
            oe = e;
        }
    }
}

int main() {
    freopen("milk.in", "r", stdin);
    // freopen("milk.out", "w", stdout);
    initialize();

    for (int i = 1; i <= n; i++) {
        if (is_intersect(as, ae, intervals[i].s, intervals[i].t)) {
            ae = max(ae, intervals[i].t);
        } else {
            if (length_of(le, intervals[i].s) > length_of(ns, ne)) {
                ns = le;
                ne = intervals[i].s;
            }

            if (!is_intersect(ls, le, intervals[i].s, intervals[i].t)) {
                ls = intervals[i].s;
            }
        }

        le = max(le, intervals[i].t);

        if (length_of(ls, le) > length_of(as, ae)) {
            as = ls;
            ae = le;
        }

        //		printf("a: (%d, %d); n: (%d %d)\n",as,ae,ns,ne);
    }

    output();
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &intervals[i].s, &intervals[i].t);
    }

    sort(&intervals[1], &intervals[n + 1]);

    as = ae = ls = le = ns = ne = intervals[1].s;
}

void output() { printf("%d %d", length_of(as, ae), length_of(ns, ne)); }
