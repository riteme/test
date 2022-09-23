#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int main() {
    long long a, b, c, d;
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    printf("%lld\nTakahashi\n", (a + b) * (c - d));
    return 0;
}
