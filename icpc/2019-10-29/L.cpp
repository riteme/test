

    #include <cstdio>
    #include <cstring>

    #include <algorithm>

    using namespace std;

    int main() {
        int T;
        scanf("%d", &T);
        for (int _t = 1; _t <= T; _t++) {
            int n;
            scanf("%d", &n);
            int s;
            const char *str[] = {"Sheep", "Panda", "Draw"};
            if (n & 1) {
                if (n <= 5) s = 2;
                else s = 1;
            } else {
                if (n <= 14) s = 2;
                else s = 0;
            }
            printf("Case #%d: %s\n", _t, str[s]);
        }
        return 0;
    }
