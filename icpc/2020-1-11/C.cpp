#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 10000000

static char key[2 * NMAX + 10];
static char s1[NMAX + 10];
static char s0[NMAX + 10];

int main() {
    scanf("%s%s", s1, key);

    int m = strlen(key);
    for (int i = 0; s1[i]; i++) {
        s0[i] = ((s1[i] - 'A' - (key[i] - 'A')) % 26 + 26) % 26 + 'A';
        key[m + i] = s0[i];
    }
    puts(s0);

    return 0;
}