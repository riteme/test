#include <cstdio>

#define NMAX 256

static int cnt[NMAX][NMAX];

int main() {
    freopen("subset.in", "r", stdin);
    freopen("subset.out", "w", stdout);

    int q, s;
    char command[4];
    scanf("%d", &q);

    while (q--) {
        scanf("%s%d", command, &s);

        int pre = s >> 8;
        int suf = s & 0xFF;
        if (command[0] == 'a' || command[0] == 'd') {
            int w = 1;
            
            if (command[0] == 'd')
                w = -1;

            int mask = 0xFF ^ suf;
            for (int cur = mask; cur; cur = (cur - 1) & mask)
                cnt[pre][cur | suf] += w;
            cnt[pre][suf] += w;
        } else {
            int answer = cnt[0][suf];
            for (int cur = pre; cur; cur = (cur - 1) & pre)
                answer += cnt[cur][suf];

            printf("%d\n", answer);
        }
    }
}
