#include <cctype>
#include <cstdio>
#include <cstring>

static char K[2000];
static char C[2000];
static char M[2000];
static int Kcode[2000];
static int Ccode[2000];
static int Mcode[2000];

int main() {
    scanf("%s%s", K, C);

    int lenK = strlen(K);
    int lenC = strlen(C);

    for (int i = 0; i < lenK; i++) {
        Kcode[i] = tolower(K[i]) - 'a';
    }  // for

    for (int i = 0; i < lenC; i++) {
        Ccode[i] = tolower(C[i]) - 'a';
    }  // for

    int pos = 0;
    for (int i = 0; i < lenC; i++) {
        Mcode[i] = (Ccode[i] - Kcode[pos]) % 26;

        pos++;
        pos %= lenK;
    }  // for

    for (int i = 0; i < lenC; i++) {
        int code = Mcode[i];

        if (code < 0)
            code += 26;

        char c = code + 'a';
        if (isupper(C[i]))
            c = toupper(c);
        putchar(c);
    }  // for

    putchar('\n');

    return 0;
}  // function main
