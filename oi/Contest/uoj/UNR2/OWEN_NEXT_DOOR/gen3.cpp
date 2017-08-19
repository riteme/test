#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 100000

static struct Char {
    char a, b;

    bool operator!=(const Char &r) const {
        return a != r.a && b != r.b && a != r.b && b != r.a;
    }
} str[NMAX + 10];

int main() {
    int n, _;
    scanf("%d%d%d%d", &n, &_, &_, &_);

    char buf[4];
    for (int i = 1; 3 * i < n; i++) {
        scanf("%s", buf);
        scanf("%s", buf);
        str[i].a = buf[0];
        scanf("%s", buf);
        str[i].b = buf[0];
    }  // for

    int ans = 0;
    n /= 3;
    for (int i = 1; i <= n; i++) {
        int j;
        for (j = i - 1; j >= 1 && 2 * i - j <= n; j--) {
            if (str[j] != str[2 * i - j])
                break;
        }

        j++;
        ans = max(ans, 2 * (i - j) + 1);
    }  // for

    for (int i = 1; i < n; i++) {
        int j;
        for (j = i; j >= 1 && 2 * i - j + 1 <= n; j--) {
            if (str[j] != str[2 * i - j + 1])
                break;
        }

        j++;
        ans = max(ans, 2 * (i - j + 1));
    }  // for

    printf("%d\n", 2 * ans + 1);

    return 0;
}  // function main
