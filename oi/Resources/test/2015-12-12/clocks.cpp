#include <climits>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

#define STATUS_SIZE 262144

static int data[4][4];
static bool marked[STATUS_SIZE + 10];
static int min_value;

struct Status {
    Status() : a(0), b(0), c(0), d(0), e(0), f(0), g(0), h(0), i(0), count(0) {}

    int a, b, c, d, e, f, g, h, i;
    int count;
};  // struct Status

void initialize();
void output();
int turn_into();
Status generate_status();

inline int f(int x) { return (x / 3) % 4; }

inline int h(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
    return a + (b << 2) + (c << 4) + (d << 6) + (e << 8) + (f << 10) +
           (g << 12) + (h << 14) + (i << 16);
}

inline int h(const Status &s) {
    return h(s.a, s.b, s.c, s.d, s.e, s.f, s.g, s.h, s.i);
}

inline Status increase(const Status &s, int type) {
    Status r = s;

    switch (type) {
        case 1: r.a++, r.b++, r.d++, r.e++; break;
        case 2: r.a++, r.b++, r.c++; break;
        case 3: r.b++, r.c++, r.e++, r.f++; break;
        case 4: r.a++, r.d++, r.g++; break;
        case 5: r.b++, r.d++, r.e++, r.f++, r.h++; break;
        case 6: r.c++, r.f++, r.i++; break;
        case 7: r.d++, r.e++, r.g++, r.h++; break;
        case 8: r.g++, r.h++, r.i++; break;
        case 9: r.e++, r.f++, r.h++, r.i++; break;
    }  // switch to type

    r.a %= 4, r.b %= 4, r.c %= 4, r.d %= 4, r.e %= 4, r.f %= 4, r.g %= 4,
        r.h %= 4, r.i %= 4;
    r.count++;

    return r;
}

int main() {
    // freopen("clocks.in", "r", stdin);
    // freopen("clocks.out","w",stdout);
    initialize();

    min_value = turn_into();

    output();
    fclose(stdin);
    fclose(stdout);
    return 0;
}

Status generate_status() {
    Status s;
    s.a = f(data[1][1]), s.b = f(data[1][2]), s.c = f(data[1][3]),
    s.d = f(data[2][1]), s.e = f(data[2][2]), s.f = f(data[2][3]),
    s.g = f(data[3][1]), s.h = f(data[3][2]), s.i = f(data[3][3]);

    return s;
}

int turn_into() {
    fill(&marked[0], &marked[STATUS_SIZE + 10], false);
    int goal = 0;

    queue<Status> q;
    q.push(generate_status());

    while (not q.empty()) {
        Status current = q.front();
        q.pop();

        if (h(current) == goal) return current.count;

        for (int i = 1; i <= 9; i++) {
            Status next = increase(current, i);

            int hash = h(next);
            if (not marked[hash]) {
                marked[hash] = true;
                q.push(next);
            }
        }  // for
    }      // while

    return -1;
}

void initialize() {
    scanf("%d %d %d %d %d %d %d %d %d", &data[1][1], &data[1][2], &data[1][3],
          &data[2][1], &data[2][2], &data[2][3], &data[3][1], &data[3][2],
          &data[3][3]);

    min_value = INT_MAX;
}

void output() { printf("%d", min_value); }
