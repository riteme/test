#include <cstdio>
#include <cstring>
#include <bitset>

using namespace std;

#define NMAX 100000

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        char buffer[NMAX + 10] = { 0 };
        scanf("%s", buffer);
        int n = strlen(buffer);

        bitset<NMAX + 10> bitmap(buffer);

        int cnt = bitmap.count();
        if (cnt == 1 || cnt == n - 1)
            puts("Yes");
        else
            puts("No");
    }  // while

    return 0;
}  // function main
