// #define NDEBUG

#define NAME "challenge"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

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

	for (size_t i = 0; i < 65536; i++) {
	    vec[i].reserve(2000);
	}

	u32 u = next_integer(s);
	vec[u >> 16].push_back(u);
	for (size_t i = 1; i < n; i++) {
	    u = next_integer(u);
	    vec[u >> 16].push_back(u);
	}
    }

    virtual void main() {
	u32 *ptr = a;
	for (size_t i = 0; i < 65536; i++) {
	    radix_sort(i, ptr, vec[i].begin(), vec[i].end());
	}

	output_arr(a, n << 2);
    }

    template <typename TIterator>
    void radix_sort(u32 id, u32 *&ptr, TIterator head, TIterator tail) {
	// memset(bucket, 0, sizeof(bucket));
	u32 mask = (1 << 16) - 1;
	u32 idx = id << 16;
	for (; head != tail; head++) {
	    bucket[*head & mask]++;
	}

	for (u32 i = 0; i < 65536; i++) {
	    // u32 c = bucket[i];
	    // while (c--) {
	    while (bucket[i]) {
		bucket[i]--;
		*ptr = idx + i;
		ptr++;
	    }
	}
    }

 private:
    static const int NMAX = 100000000;
    size_t n;
    u32 a[NMAX + 10];
    u32 bucket[65536];
    vector<u32> vec[65536];
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
    }

    solver->main();

    return 0;
}
