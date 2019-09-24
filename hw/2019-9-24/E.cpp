#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 1000

typedef long long i64;

static int n;
static i64 seq[NMAX + 10];
static deque<i64> q;
static int cnt, op[NMAX + 10];

inline void take(int i) {
    op[cnt++] = i;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
        q.push_back(seq[i]);
    }
    while (!q.empty() && q[0] <= 0) {
        take(1);
        q.pop_front();
    }
    while (!q.empty() && q.back() <= 0) {
        take(q.size());
        q.pop_back();
    }

    if (q.empty()) {
        int vi = max_element(seq + 1, seq + n + 1) - seq;
        printf("%lld\n%d\n", seq[vi], n - 1);
        for (int i = n; i > vi; i--)
            printf("%d\n", i);
        for (int i = 1; i < vi; i++)
            puts("1");
        return 0;
    }

    i64 s1 = 0, s2 = 0;
    for (int i = 0; i < q.size(); i += 2)
        s1 += max(0LL, q[i]);
    for (int i = 1; i < q.size(); i += 2)
        s2 += max(0LL, q[i]);

    if (s1 >= s2) {
        for (int i = 2; i < q.size() - 1; i += 2) if (q[i] <= 0) {
            take(i + 1);
            q[i - 1] += q[i + 1];
            q.erase(q.begin() + i);
            q.erase(q.begin() + i);
            i -= 2;
        }
        while (q.size() > 2) {
            take(2);
            i64 v = q[0] + q[2];
            q.pop_front();
            q.pop_front();
            q.pop_front();
            q.push_front(v);
        }
        if (q.size() == 2) {
            take(2);
            q.pop_back();
        }
    } else {
        for (int i = 1; i < q.size() - 1; i += 2) if (q[i] <= 0) {
            take(i + 1);
            q[i - 1] += q[i + 1];
            q.erase(q.begin() + i);
            q.erase(q.begin() + i);
            i -= 2;
        }
        while (q.size() > 3) {
            take(3);
            i64 v = q[1] + q[3], u = q[0];
            q.pop_front();
            q.pop_front();
            q.pop_front();
            q.pop_front();
            q.push_front(v);
            q.push_front(u);
        }
        if (q.size() == 3) {
            take(3);
            q.pop_back();
            take(1);
            q.pop_front();
        }
        if (q.size() == 2) {
            take(1);
            q.pop_front();
        }
    }

    printf("%lld\n%d\n", q[0], cnt);
    for (int i = 0; i < cnt; i++)
        printf("%d\n", op[i]);

    return 0;
}
