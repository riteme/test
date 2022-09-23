#include <cstdio>
#include <cstdlib>

using u64 = unsigned long long;

void fuck() {
    puts("-1");
    exit(0);
}

int main() {
    u64 n, m;
    scanf("%llu%llu", &n, &m);
    char S[128];
    scanf("%s", S);
    u64 i = 0;
    while (S[i] != 0 && S[i] != '.') {
        i++;
    }
    u64 K = atoll(S) * 2;
    if (S[i] == '.') {
        if (S[i + 1] == '5')
            K++;
        else
            fuck();
    }
    if (K > 2 * n * m)
        fuck();
    u64 w = K / (2 * n);
    u64 h = K % (2 * n);
    if (w == 0) {
        if (K % 2) {
            puts("5");
            puts("0 0");
            puts("")
        }
    }
}
