#include <cstdio>
#include <cstring>

#include <string>
#include <algorithm>

using namespace std;

static int mi = 0x3f3f3f3f;
static string mistr;

static string str;
static int HPA, HPB, ATKA, ATKB;

void dfs(int i, int A, int B, int s) {
    if (s > mi) return;
    if (A <= 0 && B <= 0) {
        if (s < mi) {
            mi = s;
            mistr = str;
        } else if (s == mi) {
            if (mistr.empty() || str < mistr) {
                mistr = str;
            }
        }
        return;
    }
    if (A > 0) {
        str.push_back('A');
        dfs(i + 1, A - i, B, s + (A > 0 ? ATKA : 0) + (B > 0 ? ATKB : 0));
        str.pop_back();
    }
    if (B > 0) {
        str.push_back('B');
        dfs(i + 1, A, B - i, s + (A > 0 ? ATKA : 0) + (B > 0 ? ATKB : 0));
        str.pop_back();
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &HPA, &HPB, &ATKA, &ATKB);
        mistr.clear();
        mi = 0x3f3f3f3f;
        dfs(1, HPA, HPB, 0);
        printf("%d %s\n", mi, mistr.data());
    }
    return 0;
}
