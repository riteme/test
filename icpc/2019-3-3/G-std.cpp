#include <cstdio>

//FILE *fin = fopen("a.in", "r"), *fout = fopen("a.out", "w");
#define fin stdin
#define fout stdout

#define CAT 300003
#define LIM 500009

double v[LIM], add[LIM];
int h;

inline void baga(int a, int b, int x, int y) {
    if (b == y) {
        add[b - h + CAT] += x - a;
        add[b + 1 + CAT] -= x - a;
        return ;
    }
    if (b < y)
        b ^= y ^= b ^= y;
    double u = (x - a) / (double) (b - y);
    v[y - h + CAT] += u;
    v[b - h + CAT] -= u;
    v[y + CAT] -= u;
    v[b + CAT] += u;
}

int main() {
    int n;
    fscanf(fin, "%d%d", &n, &h);

    int a = 0, b = 0;
    for (int i = 1; i <= n; i++) {
        int x, y;
        fscanf(fin, "%d%d", &x, &y);

        baga(a, b, x, y);

        a = x;
        b = y;
    }

    double ans = 0, acum = 0, panta = 0, sc = 0;
    for (int i = 0; i < LIM; i++) {
        acum += panta;
        panta += v[i];
        sc += add[i];
        if (acum + sc > ans)
            ans = acum + sc;
    }

    fprintf(fout, "%.12f\n", ans);

    fclose(fin);
    fclose(fout);
    return 0;
}
