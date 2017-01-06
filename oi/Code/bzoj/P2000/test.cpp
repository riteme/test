#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 1000000

typedef long long int64;

static int n;
static int64 seq[NMAX + 10];

struct Compare {
    bool operator()(const int a, const int b) const {
        return seq[a] < seq[b];
    }
};

static priority_queue<int, vector<int64>, Compare> q; 

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
    }

    for (int i = 1; i <= n; i++) {
        if (seq[i] == 0) {
            if (i > 1)
                q.push(i - 1);
            if (i < n)
                q.push(i + 1);
        }
    }

    int64 p1 = 0, p2 = 0;
    int64 *current = &p1, *last = &p2;
    while (!q.empty()) {
        int p = q.top();
        q.pop();
        *current += seq[p];
        seq[p] = 0;

        if (p > 1 && seq[p - 1])
            q.push(p - 1);
        if (p < n && seq[p + 1])
            q.push(p + 1);
        
        swap(current, last);
    }

    printf("%lld %lld\n", p1, p2);

    return 0;
}
