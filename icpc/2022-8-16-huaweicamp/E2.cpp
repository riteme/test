#include <bits/stdc++.h>

#define L 24
#define B 320
#define N 100005

using namespace std;

int a[N], o[N], small[N], big[2][N], bl[B], bu[B], n, m, b;

void update_small(int p) {
    for (int i = p, k = 0; i <= n + 1; i++) {
        k += a[i];

        if (k > L) {
            small[p] = i;
            return;
        }
    }
}

void update_big(int q) {
    for (int i = bu[q]; i >= bl[q]; i--) {
        if (o[small[i]] == o[i]) {
            big[0][i] = big[0][small[i]];
            big[1][i] = big[1][small[i]] + 1;
        } else {
            big[0][i] = small[i];
            big[1][i] = 1;
        }
    }
}
void operate() {
    static int z, x, y;
    cin >> z >> x >> y;
    if (z == 1) {
        static int q[L + 2] = {0};
        a[x] = y;
        q[0] = 0;

        for (int i = 0; i < x && i < L; i++) {
            update_small(x - i);
            if (!q[0] || q[q[0]] != o[x - i])
                q[++q[0]] = o[x - i];
        }

        while (q[0])
            update_big(q[q[0]--]);
    } else {
        int w = 0;

        while (big[0][x] <= y) {
            w += big[1][x];
            x = big[0][x];
        }

        while (x <= y) {
            ++w;
            x = small[x];
        }

        cout << w << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    b = ceil(sqrt(n));

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        o[i] = i / b;
    }

    a[n + 1] = L;
    o[n + 1] = n / b + 1;

    for (int i = 0; i <= o[n + 1]; i++) {
        bl[i] = n + 2;
        bu[i] = 0;
    }

    for (int i = 1; i <= n + 1; i++) {
        bl[o[i]] = min(bl[o[i]], i);
        bu[o[i]] = max(bu[o[i]], i);
    }

    for (int i = 1; i <= n; i++)
        update_small(i);
    for (int i = o[n + 1] - 1; i >= 0; i--)
        update_big(i);

    while (m--)
        operate();
    return 0;
}
