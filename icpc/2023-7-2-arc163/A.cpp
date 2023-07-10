#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int n;
char s[5000];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &n, s);
        bool okay = false;
        for (int i = 1; i < n; i++) {
            int j = 0;
            for (; j < i; j++) {
                if (s[j] != s[i + j])
                    break;
            }
            if (j < i && s[j] < s[i + j]) {
                okay = true;
                break;
            }
            if (j == i && i < n - i) {
                okay = true;
                break;
            }
        }

        puts(okay ? "Yes" : "No");
    }
    return 0;
}
