#include <cstdio>

#include <unordered_map>

using namespace std;

#define NMAX 1000000000

int main() {
    unordered_map<int, int> s;
    int n;
    scanf("%d", &n);

    for (int i = 0; i * i <= NMAX; i++) {
        s[i * i] = i;
    }

    int cnt = 0;
    for (int i = 0; i * i <= NMAX; i++) {
        int r = n - i * i;
        if (s.count(r)) {
            if (s[r] < i)
                break;

            printf("%d %d\n", i, s[r]);
            cnt++;
        }
    }

    if (cnt == 0)
        printf("No Solution\n");

    return 0;
}
