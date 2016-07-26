#include <cstdio>
#include <regex>

using namespace std;

#define NMAX 200000

static char text[NMAX + 10];
static char pattern[NMAX + 10];

int main() {
    pattern = ".*";
    scanf("%s%s", text, pattern + 2);
    for (int i = 2; pattern[i] != '\0'; i++)
        if (pattern[i] == '?')
            pattern[i] = '.';

    regex matcher(pattern + 2);
    puts(regex_match(text, matcher) ? "YES" : "NO");

    return 0;
}  // function main
