#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int main() {
#ifdef USE_FILE_IO
    freopen("years.in", "r", stdin);
    freopen("years.out", "w", stdout);
#endif
    double n, m;
    scanf("%lf%lf", &n, &m);
    printf("%lf\n", (n + 1) / (n - m + 1) * 0.5);

    return 0;
}
