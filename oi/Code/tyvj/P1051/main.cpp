// P1051 选课

#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define NMAX 300
#define MMAX 300

typedef pair<int, int> Lesson;

template <>
struct less<Lesson> {
    bool operator()(const Lesson &a, const Lesson &b) const {
        return a.second < b.second;
    }
};  // struct less

static int n, m;
static int w[NMAX + 10];
static int d[NMAX + 10];
static int f[MMAX + 10][NMAX + 10];
static priority_queue<Lesson> s;

void initialize();
void output();

int main() {
    ios::sync_with_stdio(false);
    initialize();

    output();
    return 0;
}  // function main

void initialize() {
    std::fill(std::begin(f), std::end(f), 0);
    std::fill(std::begin(d), std::end(d), 0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int p;
        cin >> w[i] >> p;

        d[i] = d[p] + 1;

        s.push(Lesson(i, d[i]));
    }
}

void output() {}
