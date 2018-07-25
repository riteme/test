#include <cstdio>
#include <algorithm>

using namespace std;

static int n;
static char buffer[1000];

int main() {
    scanf("%d", &n);
    scanf("%s", buffer);

    bool inpar = false;
    int lenanswer = 0;
    int len = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        char c = buffer[i];

        if (c == '(') {
            inpar = true;

            lenanswer = max(lenanswer, len);
            len = 0;
        } else if (c == ')') {
            inpar = false;

            if (len > 0)
                cnt++;

            len = 0;
        } else if (c == '_') {
            if (inpar && len > 0)
                cnt++;
            else if (!inpar)
                lenanswer = max(lenanswer, len);

            len = 0;
        } else {
            len++;
        }
    }  // for

    lenanswer = max(lenanswer, len);
    printf("%d %d", lenanswer, cnt);

    return 0;
}  // function main
