#include <cassert>
#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int pcnt, pr[NMAX + 10];
static bool mark[NMAX + 10];

void sieve() {
    for (int i = 2; i <= NMAX; i++) {
        if (!mark[i])
            pr[pcnt++] = i;
        for (int j = 0; pr[j] * i <= NMAX; j++) {
            mark[pr[j] * i] = true;
            if (i % pr[j] == 0)
                break;
        }
    }
}

struct Orbit {
    int p, s;

    Orbit next() const {
        return {p + s, s};
    }

    bool operator<(const Orbit &z) const {
        return p > z.p;
    }
};

int main() {
    sieve();

    priority_queue<Orbit> q;
    q.push({1, 2});
    q.push({2, 3});
    q.push({1, 5});
    q.push({3, 7});
    q.push({1, 11});
    q.push({4, 13});
    //q.push({1, 2});
    //q.push({2, 3});
    //q.push({3, 5});
    //q.push({3, 7});
    //q.push({6, 11});
    //q.push({3, 13});
    //q.push({5, 17});
    //q.push({12, 19});
    //q.push({7, 23});
    //q.push({4, 29});
    //q.push({6, 31});
    memset(mark, 0, sizeof(mark));
    int j = 6;
    for (int i = 1; i <= NMAX; i++) {
        //printf("i = %d\n", i);
        while (q.top().p == i) {
            mark[i] = true;
            auto o = q.top();
            q.pop();
            q.push(o.next());
        }
        if (!mark[i]) {
            printf("⇒ j = %d [pr[j] = %d, i = %d]\n", j, pr[j], i);
            assert(pr[j] < i);
            mark[i] = true;
            q.push({i + pr[j], pr[j]});
            j++;
        }
    }

    return 0;
}
