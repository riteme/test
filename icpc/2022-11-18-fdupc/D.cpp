#include <cstdio>
#include <cstring>

#include <string>
#include <unordered_map>

using namespace std;

struct fuck {
    int a, b, c, d, e, f, shit;
};

int rnd(double sb) {
    return sb * 10 + 0.5;
}

int n, m;
std::unordered_map<int, std::unordered_map<std::string, std::unordered_map<std::string, fuck>>> aha;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        double s;
        scanf("%lf", &s);
        fuck fu;
        fu.shit = rnd(s);
        double a, b, c, d, e, f;
        scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f);
        fu.a = rnd(a);
        fu.b = rnd(b);
        fu.c = rnd(c);
        fu.d = rnd(d);
        fu.e = rnd(e);
        fu.f = rnd(f);
        aha[fu.shit]["Male"]["Junior"] = fu;
        scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f);
        fu.a = rnd(a);
        fu.b = rnd(b);
        fu.c = rnd(c);
        fu.d = rnd(d);
        fu.e = rnd(e);
        fu.f = rnd(f);
        aha[fu.shit]["Male"]["Senior"] = fu;
        scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f);
        fu.a = rnd(a);
        fu.b = rnd(b);
        fu.c = rnd(c);
        fu.d = rnd(d);
        fu.e = rnd(e);
        fu.f = rnd(f);
        aha[fu.shit]["Female"]["Junior"] = fu;
        scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f);
        fu.a = rnd(a);
        fu.b = rnd(b);
        fu.c = rnd(c);
        fu.d = rnd(d);
        fu.e = rnd(e);
        fu.f = rnd(f);
        aha[fu.shit]["Female"]["Senior"] = fu;
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        char p[100], q[100];
        scanf("%s%s", p, q);
        double A, B, C, D, E, F, G;
        scanf("%lf%lf%lf%lf%lf%lf%lf", &A, &B, &C, &D, &E, &F, &G);
        int a0, b0, c0, d0, e0, g0, f0;
        a0 = rnd(A);
        b0 = rnd(B);
        c0 = rnd(C);
        d0 = rnd(D);
        e0 = rnd(E);
        f0 = rnd(F);
        g0 = rnd(G);
        int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0;
        for (auto &u : aha) {
            fuck fu = u.second[p][q];
            if (a0 <= fu.a)
                a = max(a, u.first);
            if (b0 <= fu.b)
                b = max(b, u.first);
            if (c0 >= fu.c)
                c = max(c, u.first);
            if (d0 >= fu.d)
                d = max(d, u.first);
            if (e0 >= fu.e)
                e = max(e, u.first);
            if (f0 >= fu.f)
                f = max(f, u.first);
        }
        if (p[0] == 'M') {
            if (g0 >= 280)
                g = 600;
            if (g0 <= 178 || (240 <= g0 && g0 <= 279))
                g = 800;
            if (179 <= g0 && g0 <= 239)
                g = 1000;
        } else {
            if (g0 >= 280)
                g = 600;
            if (g0 <= 171 || (240 <= g0 && g0 <= 279))
                g = 800;
            if (172 <= g0 && g0 <= 239)
                g = 1000;
        }
        int nima = a * 20 + b * 20 + c * 10 + d * 10 + e * 10 + f * 15 + g * 15;
        if (nima % 10 >= 5)
            nima += 10 - nima % 10;
        int x = nima / 1000;
        int y = nima % 1000 / 10;
        printf("%d.%02d\n", x, y);
    }
    return 0;
}
