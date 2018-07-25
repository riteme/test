#include <cctype>
#include <cstdio>

static int p1, p2, p3;
static size_t pos;
static char input[2000000];
static char buffer[2000000];

static void expand(char from, char to) {
    char beg, end, step;

    if (p3 == 1) {
        beg = from + 1;
        end = to;
        step = 1;
    } else {
        beg = to - 1;
        end = from;
        step = -1;
    }

    for (char c = beg; c != end; c += step) {
        char mask = c;

        if (p1 == 2)
            mask = toupper(mask);
        else if (p1 == 3)
            mask = '*';

        for (int cnt = 0; cnt < p2; cnt++) {
            buffer[pos++] = mask;
        }  // for
    }      // for
}

int main() {
    scanf("%d%d%d%s", &p1, &p2, &p3, input);

    for (size_t i = 0; input[i]; i++) {
        char c = input[i];

        if (c == '-') {
            if (i > 0 && ((isalpha(input[i - 1]) && isalpha(input[i + 1])) ||
                          (isdigit(input[i - 1]) && isdigit(input[i + 1]))) &&
                input[i - 1] < input[i + 1]) {
                expand(input[i - 1], input[i + 1]);
            } else
                buffer[pos++] = c;
        } else
            buffer[pos++] = c;
    }  // for

    printf("%s\n", buffer);

    return 0;
}  // function main
