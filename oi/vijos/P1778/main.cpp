#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

#define NMAX 1000

static int klen, slen;
static char k[NMAX + 10];
static char M[NMAX + 10];
static char C[NMAX + 10];
static char kc[NMAX + 10];
static char Mc[NMAX + 10];
static char Cc[NMAX + 10];

static void initialize() {
    scanf("%s%s", k, C);
    klen = strlen(k);
    slen = strlen(C);
}

int main() {
    initialize();

    for (int i = 0; i < klen; i++) {
        kc[i] = tolower(k[i]) - 'a';
    }  // for

    for (int i = 0; i < slen; i++) {
        Cc[i] = tolower(C[i]) - 'a';
    }  // for

    int pos = 0;
    for (int i = 0; i < slen; i++) {
        Mc[i] = Cc[i] - kc[pos];
        if (Mc[i] < 0)
            Mc[i] += 26;

        pos++;
        pos %= klen;
    }  // for

    for (int i = 0; i < slen; i++) {
        M[i] = Mc[i] + 'a';
        if (isupper(C[i]))
            M[i] = toupper(M[i]);
    }  // for

    printf("%s\n", M);

    return 0;
}  // function main
