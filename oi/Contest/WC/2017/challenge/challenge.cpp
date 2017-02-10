// #define NDEBUG

#define NAME "challenge"

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <bitset>

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
    u32 blocks = size / 4;
    u32 *A = (u32 *) a;
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

        memset(tail, 0, sizeof(tail));
        u32 u = next_integer(s);
        push_bucket(u);
        for (size_t i = 1; i < n; i++) {
            u = next_integer(u);
            push_bucket(u);
        }
    }

    virtual void main() {
        for (size_t i = 0; i < (1 << 24); i++) {
            count_sort(&bucket[i][0], &bucket[i][tail[i]], i);
        }

        u32 *pos = &bucket[0][0] + tail[0];
        for (size_t i = 1; i < (1 << 24); i++) {
            memmove(pos, &bucket[i][0], tail[i] << 2);
            pos += tail[i];
        }

        output_arr(bucket, n << 2);
    }

 private:
    static const int NMAX = 200000000;

    void push_bucket(const u32 v) {
        u32 id = v >> 10;
        bucket[id][tail[id]++] = v;
        // assert(tail[id] <= 64);
    }

    void count_sort(u32 *first, u32 *last, u32 id) {
        const u32 mask = (1 << 10) - 1;
        const u32 head = id << 10;

        memset(cnt, 0, sizeof(cnt));
        for (u32 *beg = first; beg != last; beg++) {
            cnt[*beg & mask]++;
        }

        for (u32 i = 0; i < (1 << 10); i++) {
            for (u32 j = 0; j < cnt[i]; j++, first++) {
                *first = head + i;
            }
        }
    }

    size_t n;
    size_t tail[1 << 24];
    u32 bucket[1 << 24][64];
    u32 cnt[1 << 10];
};

class Solver2 : public Solver {
 public:
    typedef bitset<900000> Bitmap;

    Solver2() {
        scanf("%d%d", &n, &q);
        scanf("%s%s", m1, m2);

        for (int i = 0; i < n; i++) {
            switch (m1[i]) {
                case '2': s1.set(3 * i); break;
                case '0': s1.set(3 * i + 1); break;
                case '1': s1.set(3 * i + 2); break;
            }

            switch (m2[i]) {
                case '0': s2.set(3 * i); break;
                case '1': s2.set(3 * i + 1); break;
                case '2': s2.set(3 * i + 2); break;
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
        l *= 3;
        r *= 3;
        r += 2;
        return (b >> l) << (b.size() - r - 1 + l);
    }

    u32 query(int x, int y, int l) {
        return (cut(s1, x, x + l - 1) & cut(s2, y, y + l - 1)).count();
    }

 private:
    int n, q;
    u32 answer[300010];
    char m1[300010], m2[300010];
    Bitmap s1, s2;
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
