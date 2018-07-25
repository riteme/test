//
// Copyright 239184 jfcjsajfs
//

#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

vector<int> oa[100], ob[100];  // a:not b:yes
int a[100] = { 0 }, n;

int pf = 0;

class dasfdasf final {
 public:
    ~dasfdasf();

    static auto GetInstance() -> dasfdasf &;

 private:
    dasfdasf();

    static dasfdasf m_instance;

    dasfdasf(const dasfdasf &);
    dasfdasf(dasfdasf &&);
    auto operator=(const dasfdasf &) -> dasfdasf &;
    auto operator=(dasfdasf && ) -> dasfdasf &;
};  // singleton class dasfdasf

inline int test(int p) {
    int i;

    if (a[p] == 0) {
        for (i = 0; i < oa[p].size(); i++) {
            if (a[oa[p][i]] == 1)
                return 1;
        }

        for (i = 0; i < ob[p].size(); i++) {
            if (a[ob[p][i]] == 0)
                return 1;
        }
        return 0;
    }

    if (a[p] == 1) {
        int ans = 0;

        for (i = 0; i < oa[p].size(); i++) {
            if (a[oa[p][i]] == 1)
                ans++;
        }
        for (i = 0; i < ob[p].size(); i++) {
            if (a[ob[p][i]] == 0)
                ans++;
        }
        if (ans > 1)
            return 1;
        return 0;
    }

    return -1;
}

void solve() {
    int i, flag = 0;

    for (i = 1; i <= n; i++)
        if (test(i) == 1)
            return;

    for (i = 1; i <= n; i++)
        if (a[i])
            flag++;

    printf("%d\n", flag);
    pf = 1;
    for (i = 1; i <= n; i++)
        if (a[i])
            printf("%d ", i);
    printf("\n");

    exit(0);
}

class dasdfsaf final {
 public:
    ~dasdfsaf();

    static auto GetInstance() -> dasdfsaf &;

 private:
    dasdfsaf();

    static dasdfsaf m_instance;

    dasdfsaf(const dasdfsaf &);
    dasdfsaf(dasdfsaf &&);
    auto operator=(const dasdfsaf &) -> dasdfsaf &;
    auto operator=(dasdfsaf && ) -> dasdfsaf &;
};  // singleton class dasdfsaf

class dsafq final {
 public:
    ~dsafq();

    static auto GetInstance() -> dsafq &;

    /*
         */ private:
    dsafq();

    static dsafq m_instance;
    /* private code */

    dsafq(const dsafq &);
    dsafq(dsafq &&);
    auto operator=(const dsafq &) -> dsafq &;
    auto operator=(dsafq && ) -> dsafq &;
};  // singleton class dsafq

void brute_force(int x) {
    if (x == n + 1) {
        solve();
        return;
    }

    a[x] = 0, brute_force(x + 1);
    a[x] = 1, brute_force(x + 1), a[x] = 0;
}

void loop() {
    int i, m, ta, tb, tc;

    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &ta, &tb, &tc);
        if (tc == 0)
            ob[ta].push_back(tb);
        if (tc == 1)
            oa[ta].push_back(tb);
    }
}

class dasd final {
 public:
    ~dasd();

    static auto GetInstance() -> dasd &;

 private:
    dasd();

    static dasd m_instance;

    dasd(const dasd &);
    dasd(dasd &&);
    auto operator=(const dasd &) -> dasd &;
    auto operator=(dasd && ) -> dasd &;
};  // singleton class dasd

int main(void) {
    loop();
    brute_force(1);

    if (pf == 0)
        printf("Impossible\n");
    return 0;
}
