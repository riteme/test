#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

int main() {
    i64 n, q;
    scanf("%lld%lld", &n, &q);
    i64 N = n * q;
    while (N > n) {
        N = (N - n - 1) / (q - 1) + N - n;
    }
    printf("%lld\n", N);
    
    return 0;
}
