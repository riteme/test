#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 500;

int n, m;
int cnt[NMAX];
bool a[NMAX][NMAX];

bool check(int l, int r, bool cnt_check = true) {
    l = max(l, 1);
    r = min(r, m);
    for (int j = l; j <= r; j++) {
        for (int i = 1; i <= n; i++) {
            if ((a[i][j] && a[i][j - 1]) || (a[i - 1][j] && a[i][j]))
                return false;

        }
    }

    if (cnt_check) {
        for (int j = l; j <= r; j++) {
            int c = 0;
            for (int i = 1; i <= n; i++)
                if (a[i][j])
                    c++;
            if (c != cnt[j])
                return false;
        }
    }

    return true;
}

void clear(int j) {
    for (int i = 1; i <= n; i++) {
        a[i][j] = 0;
    }
}

void place(int l, int r, int rev) {
    if (r < l)
        return;

    for (int j = rev ? r : l; rev ? j >= l : j <= r; rev ? j-- : j++) {
        int b;
        for (b = rev ? n : 1; rev ? b >= 1 : b <= n; rev ? b-- : b++) {
            if (!a[b][j - 1] && !a[b][j + 1])
                break;
        }

        for (int c = 0; (rev ? b >= 1 : b <= n) && c < cnt[j]; (rev ? b -= 2: b += 2), c++) {
            a[b][j] = 1;
        }
    }
}

bool fill(int l, int r) {
    for (int k = l; k <= r; k++) {
        place(l, k - 1, 0);
        place(k + 1, r, 1);

        for (int c = 0; c <= cnt[k]; c++) {
            int d = cnt[k] - c;

            cnt[k] = c;
            place(k, k, 0);
            cnt[k] = d;
            place(k, k, 1);
            cnt[k] = c + d;

            if (check(k - 1, k + 1))
                return true;

            clear(k);
        }

        for (int j = l; j <= r; j++) {
            clear(j);
        }
    }

    return false;
}

bool solve() {
    int mi = (n + 1) / 2;

    for (int i = 1; i <= m; i++) {
        if (i > 1 && cnt[i] + cnt[i - 1] > n)
            return false;
        if (cnt[i] > mi)
            return false;
    }
    if (n & 1) {
        for (int i = 1; i <= m; i++) {
            if (cnt[i] == mi) {
                for (int j = 1; j <= n; j += 2) {
                    a[j][i] = 1;
                }
            }
        }
    }

    if (!check(1, m, false))
        return false;

    int L = 1;
    for (int i = 1; i <= m; i++) {
        if ((n & 1) && cnt[i] == mi) {
            if (i > L && !fill(L, i - 1))
                return false;
            L = i + 1;
        }
    }

    if (L <= m)
        place(L, m, 0);

    return check(1, m);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", cnt + i);
    }

    if (solve()) {
        puts("Yes");
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                putchar(a[i][j] ? '1' : '0');
            }
            puts("");
        }
    } else {
        puts("No");
    }
    return 0;
}