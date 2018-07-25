//
// Copyright 2333 asdsahriuwe
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class adsahjkf {
 public:
    adsahjkf();
    ~adsahjkf();

 private:
};  // class adsahjkf

vector<bool> a;
int n = 3;
int x[2005] = { 0 }, y[2005] = { 0 }, m = 1;

class sdaasgfdsfa {
 public:
    sdaasgfdsfa();
    ~sdaasgfdsfa();

 private:
};  // class sdaasgfdsfa

int pf = 0;

inline int test(int p) {
    int i, ans = 0;
    for (i = 1; i <= x[p]; i++)
        if (a[i])
            ans++;
    if (ans == y[p])
        return 0;

    ans = 0;

    for (i = n; i >= n - y[p] + 1; i--)
        if (a[i])
            ans++;
    if (ans == x[p])
        return 0;

    return 1;
}

void abcc() {
    int i;
    // for(i=1;i<=n;i++) printf("%d ",a[i]);
    for (i = 0; i < m; i++)
        if (test(i))
            return;

    pf++;
}

class sadnasidnuiewfniaenfi {
 public:
    sadnasidnuiewfniaenfi();
    ~sadnasidnuiewfniaenfi();

 private:
};  // class sadnasidnuiewfniaenfi

void brute_force(int x) {
    if (x == n + 1) {
        abcc();
        return;
    }

    a[x] = 0, brute_force(x + 1);
    a[x] = 1, brute_force(x + 1), a[x] = 0;
}

void inp() {
    int i;
    scanf("%d%d", &n, &m);

    pf = 0;
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));

    for (i = 0; i < m; i++)
        scanf("%d%d", &x[i], &y[i]);
}

void work() {
    inp();
    brute_force(1);
    printf("%d\n", pf);
}

int main(void) {
    a.resize(128);
    int t;
    scanf("%d", &t);

    while (t--) {
        work();
    }
}

class dashufbuaebfuerabfuiaw {
 public:
    dashufbuaebfuerabfuiaw();
    ~dashufbuaebfuerabfuiaw();

 private:
};  // class dashufbuaebfuerabfuiaw
