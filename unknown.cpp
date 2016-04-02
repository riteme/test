#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#define add(xxx, yyy, lll) d[xxx].push_back(yyy), l[xxx].push_back(lll)
using namespace std;

struct event {
    int time, dis;
    friend bool operator<(event a, event b) {
        return a.time > b.time ? 1 : 0;
    }
};

priority_queue<event> e;

vector<int> d[20000050], l[20000050];
int lon[20000050], tim = 0, n, m;

int read() {
    int p = 1, x = 0;
    char c;

    while ((c = getchar()) >= '0' && c <= '9')
        x = x * 10 + c - '0';
    x *= p;
    return x;
}

void inp() {
    int x, y, z, i;
    // printf("%d",read());

    scanf("%d %d\n", &n, &m);

    for (i = 0; i < m; i++) {
        x = read();
        y = read();
        z = read();
        //  printf("%d-%d-%d\n",x,y,z);
        add(x, y, z);
    }
}

void pu() {
    event o;
    o = e.top();
    e.pop();

    int i, di = o.dis;
    tim = o.time;

    // printf("Now time=%d.Reach in %d.\n",tim,di);

    if (lon[di] > 0) {
        // printf("Game Over...\n");
        return;
    }

    o.time = 0;
    o.dis = 0;

    lon[di] = tim;

    for (i = 0; i < d[di].size(); i++) {
        // printf("Catch:%d len=%d. Will reach in
        // %d.\n",d[di][i],l[di][i],tim+l[di][i]);
        o.time = tim + l[di][i], o.dis = d[di][i];

        e.push(o);
    }
}

int main() {
    inp();

    event o;
    o.time = 0;
    o.dis = 1;
    e.push(o);

    for (int i = 1; i <= n; i++)
        lon[i] = -1;
    lon[1] = 0;

    while (!e.empty())
        pu();

    lon[1] = 0;
    for (int i = 1; i <= n; i++)
        printf("%d\n", lon[i]);
    printf("\n");
}
