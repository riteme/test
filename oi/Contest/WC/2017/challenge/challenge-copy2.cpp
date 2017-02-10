// #define NDEBUG

#define NAME "challenge"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

inline u32 next_integer(u32 x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

bool output_arr(void *a, u32 size) {
    if (size % 4) {
        return puts("-1"), 0;
    }
    
    u32 blocks = size / 4;
    u32 *A = (u32 *)a;
    u32 ret = size;
    u32 x = 23333333;
    for (u32 i = 0; i < blocks; i++) {
        ret = ret ^ (A[i] + x);
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
    }
    
    return printf("%u\n", ret), 1;
}

class Solver {
 public:
    virtual void main() = 0;
};

class Solver1 : public Solver {
 public:
    Solver1() {
	u32 s;
	scanf("%u%u", &n, &s);

	a[0] = next_integer(s);
	for (size_t i = 1; i < n; i++) {
	    a[i] = next_integer(a[i - 1]);
	}
    }

    virtual void main() {
	sort(a, a + n);
	output_arr(a, n << 2);
    }

 private:
    static const int NMAX = 200000000;
    size_t n;
    u32 a[NMAX + 10];
};

class Solver2 : public Solver {
 public:
    typedef bitset<300000> Bitmap;

    Solver2() {
	scanf("%d%d", &n, &q);
	scanf("%s%s", m1, m2);

	for (int i = 0; i < n; i++) {
	    switch (m1[i]) {
		case '0': a1.set(i); break;
		case '1': b1.set(i); break;
		case '2': c1.set(i); break;
	    }

	    switch (m2[i]) {
		case '0': a2.set(i); break;
		case '1': b2.set(i); break;
		case '2': c2.set(i); break;
	    }
	}
    }

    virtual void main() {
	for (int i = 0; i < q; i++) {
	    int x, y, l;
	    scanf("%d%d%d", &x, &y, &l);

	    answer[i] = query(x, y, l);
	}

	output_arr(answer, q << 2);
    }

    Bitmap cut(const Bitmap &b, int l, int r) {
	return (b >> l) << (b.size() - r - 1 + l);
    }

    u32 query(int x, int y, int l) {
	return (cut(a1, x, x + l - 1) & cut(b2, y, y + l - 1)).count() +
	       (cut(b1, x, x + l - 1) & cut(c2, y, y + l - 1)).count() +
	       (cut(c1, x, x + l - 1) & cut(a2, y, y + l - 1)).count();
    }

 private:
    int n, q;
    u32 answer[300010];
    char m1[300010], m2[300010];
    Bitmap a1, b1, c1;
    Bitmap a2, b2, c2;
};

int main() {
#ifdef NDEBUG
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif

    int taskid;
    scanf("%d", &taskid);
    Solver *solver;
    switch (taskid) {
	case 1: solver = new Solver1; break;
	case 2: solver = new Solver2; break;
    }

    solver->main();

    return 0;
}
