// NOI2015 程序自动分析

#include <cstring>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define SIZEMAX 200000
#define NMAX 100000
#define YES "YES"
#define NO "NO"

void initialize();
void quit();

struct Query {
    Query() : i(0), j(0) {}

    int i;
    int j;
};  // struct Query

static int t;
static int n;
static int s[SIZEMAX + 10];
static int eqcnt, noteqcnt;
static Query eq[NMAX + 10];
static Query noteq[NMAX + 10];
static int xcnt;
static unordered_map<int, int> hashmap;
static bool flag;

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

        eqcnt = noteqcnt = xcnt = 0;
        hashmap.clear();
        hashmap.reserve(SIZEMAX);
        make_set(SIZEMAX);
        flag = true;

        for (int opcnt = 0; opcnt < n; opcnt++) {
            int i, j, e;
            scanf("%d %d %d", &i, &j, &e);

            switch (e) {
                case 1:
                    eq[eqcnt].i = i;
                    eq[eqcnt].j = j;

                    if (hashmap.count(i) == 0) hashmap[i] = xcnt++;
                    if (hashmap.count(j) == 0) hashmap[j] = xcnt++;

                    union_set(hashmap[i], hashmap[j]);

                    eqcnt++;
                    break;
                case 0:
                    if (i == j) flag = false;

                    if (flag) {
                        noteq[noteqcnt].i = i;
                        noteq[noteqcnt].j = j;

                        noteqcnt++;
                    }
                    break;
            }  // switch to e
        }      // for

        for (int i = 0; i < noteqcnt and flag; i++) {
            Query &q = noteq[i];

            if (hashmap.count(q.i) > 0 and hashmap.count(q.j) > 0 and
                find_set(hashmap[q.i]) == find_set(hashmap[q.j]))
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
