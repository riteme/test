#include <cstdio>

#include <random>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

char query(int i, int j) {
    printf("? %d %d\n", i, j);
    fflush(stdout);
    char buf[4];
    scanf("%s", buf);
    return buf[0];
}

int p[NMAX + 10];
typedef vector<int> vi;

void solve(const vi &a, const vi &b) {
    if (a.size() == 1)
        p[a[0]] = b[0];
    if (a.size() <= 1)
        return;

    int x = a[0];
    vi al, ar, bl, br;
    for (int v : b) {
        char c = query(x, v);
        if (c == '=')
            p[x] = v;
        else if (c == '<')
            br.push_back(v);
        else
            bl.push_back(v);
    }

    for (int u : a) if (u != x) {
        char c = query(u, p[x]);
        if (c == '<')
            al.push_back(u);
        else
            ar.push_back(u);
    }

    solve(al, bl);
    solve(ar, br);
}

int main() {
    int n;
    scanf("%d", &n);
    vi a, b;
    for (int i = 1; i <= n; i++) {
        a.push_back(i);
        b.push_back(i);
    }

    random_device rd;
    mt19937_64 gen(rd());
    shuffle(a.begin(), a.end(), gen);
    shuffle(b.begin(), b.end(), gen);

    solve(a, b);

    printf("! ");
    for (int i = 1; i <= n; i++)
        printf("%d ", p[i]);
    puts("");
    return 0;
}