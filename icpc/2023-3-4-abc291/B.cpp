#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int v[1000];
    for (int i = 0; i < 5 * n; i++) {
        scanf("%d", v + i);
    }
    sort(v, v + 5 * n);
    double s = 0;
    for (int i = n; i < 4 * n; i++) {
        s += v[i];
    }
    printf("%.12lf\n", s / (3 * n));
    return 0;
}
