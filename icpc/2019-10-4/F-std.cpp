#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long double LD;
#define N 50 + 5
#define M 300 + 5
#define INF 1e30

int k, n, m, X[4], Y[4], _X[M], _Y[M];
bool Pos[M], Neg[M], Zero[M], OK[M];
LD T[M];

inline int Dot(int st_x, int st_y, int tx_1, int ty_1, int tx_2, int ty_2)
{
    int x_1 = tx_1 - st_x, y_1 = ty_1 - st_y;
    int x_2 = tx_2 - st_x, y_2 = ty_2 - st_y;
    return x_1 * x_2 + y_1 * y_2;
}

inline int Cross(int st_x, int st_y, int tx_1, int ty_1, int tx_2, int ty_2)
{
    int x_1 = tx_1 - st_x, y_1 = ty_1 - st_y;
    int x_2 = tx_2 - st_x, y_2 = ty_2 - st_y;
    return x_1 * y_2 - x_2 * y_1;
}

inline LD Dis(int x, int y)
{
    return sqrtl(x * x + y * y);
}

int main()
{
#ifdef local
    freopen("F.in", "r", stdin);
#endif
    scanf("%d", &k);
    for (int i = 0; i < 4; i ++)
        scanf("%d%d", X + i, Y + i);
    for (int t = 0; t < 2; t ++)
    {
        X[2 + t] = 2 * X[1 - t] - X[2 + t];
        Y[2 + t] = 2 * Y[1 - t] - Y[2 + t];
    }
    scanf("%d", &n);
    for (int a = 1; a <= n; a ++)
    {
        T[a] = INF;
        scanf("%d", &m);
        for (int i = 1, h; i <= m; i ++)
        {
            scanf("%d%d%d", _X + i, _Y + i, &h);
            if (h < 0)
            {
                i --, m --;
                continue;
            }
        }
        for (int t = 0; t < 2; t ++)
        {
            bool pos = false, neg = false;
            for (int i = 1, h; i <= m; i ++)
            {
                int c = Cross(X[0 + t], Y[0 + t], X[3 - t], Y[3 - t], _X[i], _Y[i]);
                pos |= (Pos[i] = (c > 0));
                neg |= (Neg[i] = (c < 0));
                Zero[i] = (c == 0);
                OK[i] = Dot(X[0 + t], Y[0 + t], X[3 - t], Y[3 - t], _X[i], _Y[i]) > 0;
            }
            if (!pos || !neg)
                continue;
            for (int i = 1; i <= m; i ++)
                for (int j = 1; j <= m; j ++)
                    if (i != j && (OK[i] || OK[j]) && (Pos[i] || Zero[i]) && (Neg[j] || Zero[j]))
                    {
                        int x_u = _X[i], y_u = _Y[i];
                        int x_v = _X[j], y_v = _Y[j];
                        int x_1 = X[0 + t], y_1 = Y[0 + t];
                        int dx = X[3 - t] - X[0 + t], dy = Y[3 - t] - Y[0 + t];
                        int fm = dx * (y_v - y_u) - dy * (x_v - x_u);
                        if (fm == 0) continue ;
                        LD tmp = LD((x_v - x_u) * (y_1 - y_u) - (y_v - y_u) * (x_1 - x_u)) / fm;
                        if (tmp > 0)
                            T[a] = min(T[a], tmp * Dis(dx, dy));
                    }
        }
    }
    sort(T + 1, T + n + 1);
    if (k < n && T[k + 1] < INF)
        printf("%.9Lf\n", T[k + 1]);
    else puts("oo");
    return 0;
}
