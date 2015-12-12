// f[i, j]=f[i-1, j]+f[i-1, j-s]
// f[j]=f[j]+f[j-s]

#include <cstdio>
#include <algorithm>

using namespace std;

#define MOD 100007
#define NMAX 500
#define SMAX 125250

static int n;
static int s;
static int f[SMAX + 10];

void initialize();
void output();

inline int get_sum(int s, int e) { return (s + e) * (e - s + 1) / 2; }

int main() {
    // freopen("subset.in","r",stdin);
    // freopen("subset.out","w",stdout);
    initialize();

    if (s % 2 == 1) {
        printf("0");
        return 0;
    }

    s /= 2;

    for (int i = 1; i <= n; i++) {
        for (int j = s; j >= i; j--) {
            f[j] += f[j - i];
            f[j] %= MOD;
        }
    }

    output();
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void initialize() {
    scanf("%d", &n);
    s = get_sum(1, n);

    fill(&f[0], &f[s + 1], 0);
    f[0] = 1;
}

void output() { printf("%d", f[s]); }
