#include <cstdio>
#include <cstring>

#include <random>
#include <algorithm>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int d;
        scanf("%d", &d);
        d = ((d - i * i) % n + n) % n;
        for (int j = 0; j < n; j++) {
            printf("%d ", (i * j + d) % n);
        }
        puts("");
    }

    return 0;
}
