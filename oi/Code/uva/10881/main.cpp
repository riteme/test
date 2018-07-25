#include <cstdio>
#include <cstring>
#include <cctype>

#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

#define NMAX 10000

static int len, T, n;
static int pos[NMAX + 10], tmp[NMAX + 10], seq[NMAX + 10], dir[NMAX + 10];
static bool turn[NMAX + 10];
static vector<int> L, R;

inline char getch() {
    char c;
    for (; !isalpha(c); c = getchar());
    return c;
}

bool cmp(int x, int y) {
    return pos[x] < pos[y];
}

void initialize() {
    memset(turn + 1, 0, n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", pos + i);
        seq[i] = i;

        char dir = getch();
        if (dir == 'L')
            L.push_back(i);
        else
            R.push_back(i);
    }

    sort(L.begin(), L.end(), cmp);
    sort(R.begin(), R.end(), cmp);
}

int main() {
    int T;
    scanf("%d", &T);
    T = 1;
    while (scanf("%d%d%d", &len, &T, &n) != EOF) {
        initialize();

        for (int i : R) {
            pos[0] = pos[i] + T * 2;
            seq[i] = *(upper_bound(L.begin(), L.end(), 0, cmp) - 1);
        }

        for (int i : L) {
            pos[0] = pos[i] - T * 2;
            seq[i] = *lower_bound(R.begin(), R.end(), 0, cmp);
        }

        for (int i : L) {
            tmp[seq[i]] = pos[i] - T * 2;
            dir[seq[i]] = -1;
        }

        for (int i : R) {
            tmp[seq[i]] = pos[i] + T * 2;
            dir[seq[i]] = 1;
        }

        memcpy(pos + 1, tmp + 1, n << 2);

        printf("Case %d:\n", T++);
        unordered_set<int> h;
        for (int i = 1; i <= n; i++) {
            if (pos[i] < 0 || pos[i] > len)
                puts("Fell off");
            else {
                printf("%d ", pos[i]);
                
                if (h.count(pos[i]))
                    puts("Turning");
                else if (dir[i] < 0)
                    puts("L");
                else
                    puts("R");

                h.insert(pos[i]);
            }
        }
    }

    return 0;
}
