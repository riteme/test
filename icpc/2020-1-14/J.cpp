#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

int convert(char c) {
    switch (c) {
        case 'A': return 0;
        case '2': return 1;
        case '3': return 2;
        case '4': return 3;
        case '5': return 4;
        case '6': return 5;
        case '7': return 6;
        case '8': return 7;
        case '9': return 8;
        case 'D': return 9;
        case 'Q': return 10;
        case 'J': return 11;
        case 'K': return 12;
    }
    return -1;
}

struct Player {
    int cnt[13];
    int star;

    int win() {
        if (star) return 0;  // exactly four cards
        for (int i = 0; i < 13; i++)
            if (cnt[i] == 4) return i + 1;
        return 0;
    }
};

Player p[100];

int solve(int n, int x) {
    while (true) {
        if (p[x].win())
            return x;

        int y = x % n + 1;
        if (p[x].star == 2) {
            p[x].star = 0;
            p[y].star = 1;
        } else {
            if (p[x].star == 1)
                p[x].star = 2;

            int mi = INT_MAX, mip;
            for (int i = 0; i < 13; i++) {
                int v = p[x].cnt[i];
                if (v && v < mi) {
                    mi = v;
                    mip = i;
                }
            }

            p[x].cnt[mip]--;
            p[y].cnt[mip]++;
        }

        if (p[x].win())  // may remove a wildcard to win
            return x;
        x = y;
    }
}

int main() {
    int n, x;
    char buf[16];
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf);
        p[i].star = 0;
        for (int j = 0; j < 4; j++)
            p[i].cnt[convert(buf[j])]++;
    }
    p[x].star = 1;

    int mi = 0, mip;
    for (int i = 1; i <= n; i++) {
        int v = p[i].win();
        if (v && (!mi || v < mi)) {
            mi = v;
            mip = i;
        }
    }

    if (!mi)
        mip = solve(n, x);
    printf("%d\n", mip);
    return 0;
}