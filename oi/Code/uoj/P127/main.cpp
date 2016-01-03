// NOI2015 程序自动分析

#include <cstring>
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

typedef int ntype;

#define SIZEMAX 100000000
#define YES "YES"
#define NO "NO"

void initialize();
void quit();

static int t;
static int n;
static int s[SIZEMAX + 1];

inline void make_set(int size) {
    int cnt = 1;
    generate_n(s + 1, size, [&cnt]() { return cnt++; });
}

inline int find_set(const int a) {
    if (a != s[a]) s[a] = find_set(s[a]);

    return s[a];
}

inline void union_set(const int a, const int b) {
    s[find_set(a)] = find_set(b);
}

int main() {
    initialize();

    for (int cnt = 0; cnt < t; cnt++) {
        scanf("%d", &n);
        bool flag = true;

        make_set(n);
        for (int k = 0; k < n and flag; k++) {
            int i, j, e;
            scanf("%d %d %d", &i, &j, &e);

            if (e == 1)
                union_set(i, j);
            else if (find_set(i) == find_set(j))
                flag = false;
        }  // for

        if (flag)
            printf(YES "\n");
        else
            printf(NO "\n");
    }  // for

    quit();
    return 0;
}  // function main

void initialize() { scanf("%d", &t); }

void quit() {}
