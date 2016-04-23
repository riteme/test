#include <cstdio>
#include <cstring>

using namespace std;

static char pattern[512];
static int prefix[512];
static char text[1000000];
static int next[1000000];
static int prev[1000000];

static void initialize() {
    scanf("%s%s", pattern + 1, text + 1);
    text[0] = '$';

    for (int i = 0; i < 1000000; i++) {
        next[i] = i + 1;
        prev[i] = i - 1;
    }  // for
    prev[0] = 0;

    prefix[0] = prefix[1] = 0;
    for (int i = 2; pattern[i] != '\0'; i++) {
        int k = prefix[i - 1];
        while (k != 0 && pattern[k + 1] != pattern[i])
            k = prefix[k];

        if (pattern[k + 1] == pattern[i])
            k++;

        prefix[i] = k;
    }  // for
}

int main() {
    initialize();

    int cnt = 0;
    int i = 0, j = 0;
    while (text[j] != '\0') {
        while (i != 0 && pattern[i + 1] != text[next[j]])
            i = prefix[i];

        if (pattern[i + 1] == text[next[j]])
            i++;

        j = next[j];

        if (pattern[i + 1] == '\0') {
            cnt++;
            int npos = next[j];

            for (int k = 0; k < i; k++)
                j = prev[j];
            next[j] = npos;
            prev[npos] = j;

            for (int k = 0; k < i; k++)
                j = prev[j];

            i = 0;
        }
    }  // while

    printf("%d\n", cnt);

    return 0;
}  // function main
