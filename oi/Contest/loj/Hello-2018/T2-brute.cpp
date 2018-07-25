#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

static int n, m;
static int str[100], sa[100], rk[100];
static vector<vector<int>> arr;

bool cmp(int x, int y) {
    while (str[x] == str[y])
        x++, y++;
    return str[x] < str[y];
}

bool is_end() {
    for (int i = 1; i <= n; i++) {
        if (str[i] != m)
            return false;
    }

    return true;
}

void inc() {
    str[n]++;
    for (int i = n; str[i] > m && i; i--) {
        str[i] = 1;
        str[i - 1]++;
    }
}

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++)
        str[i] = 1, sa[i] = i;

    str[n] = 0;
    do {
        inc();
        sort(sa + 1, sa + n + 1, cmp);
        for (int i = 1; i <= n; i++) {
            rk[sa[i]] = i;
        }

        // for (int i = 1; i <= n; i++)
        //     putchar(str[i] + 'a' - 1);
        // printf(": ");
        // for (int i = 1; i <= n; i++)
        //     printf("%d", sa[i]);
        // putchar('\n');

        arr.push_back(vector<int>(rk + 1, rk + n + 1));
    } while (!is_end());

    sort(arr.begin(), arr.end());
    auto p = unique(arr.begin(), arr.end());
    for (int i = 1; i <= n; i++)
        sa[i] = i;
    for (auto i = arr.begin(); true; i++) {
        if (i == p || !equal(i->begin(), i->end(), sa + 1)) {
            for (int j = 1; j <= n; j++)
                printf("%d", sa[j]);
            puts("");
            break;
        }

        if (!next_permutation(sa + 1, sa + n + 1))
            break;
    }

    return 0;
}
