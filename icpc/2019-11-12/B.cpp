#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>

typedef long long i64;

static char line[1024];
static int cnt[1000];
static char num[100];
static int t = 0, cur = 1;
static int lcnt = 0;

void test() {
    if (!t) return;
    for (int i = 0; i < t; i++)
        if (!isdigit(num[i])) return;
    if (t > 1 && num[0] == '0') return;
    num[t] = 0;
    i64 v = atoll(num);
    printf("%lld ", v);
    cnt[cur]++;
}

int main() {
    while (fgets(line, 1024, stdin)) {
        int len = strlen(line);
        if (len == 0) continue;
        if (line[len - 1] != '\n')
            line[len++] = '\n';
        lcnt++;
        for (int i = 0; i < len; i++) {
            char c = line[i];
            if (c == '\n') {
                if (t && !isdigit(num[t - 1]))
                    t = 0;
                break;
            }
            if (c == ' ') {
                test();
                t = 0;
            } else {
                if (i == 0 && !isdigit(c) && t) {
                    test();
                    t = 0;
                }
                if (!t) cur = lcnt;
                num[t++] = c;
            }
        }
    }
    if (t) test();
    puts("");
    for (int i = 1; i <= lcnt; i++)
        printf("%d\n", cnt[i]);
    return 0;
}
