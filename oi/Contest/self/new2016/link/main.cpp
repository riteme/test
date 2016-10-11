#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct Brick {
    Brick() {
        memset(count, 0, sizeof(count));
    }

    void append(char a) {
        count[a - 'a']++;
    }

    void append(const char *s) {
        for (size_t i = 0; s[i]; i++)
            append(s[i]);
    }

    void append(const Brick &brick) {
        for (size_t i = 0; i < 26; i++)
            count[i] += brick.count[i];
    }

    int query(char a) const {
        return count[a - 'a'];
    }

    int count[26];
};  // struct Brick

#define BUFFERSIZE 4000000
#define NMAX 5000

static int n, q;
static char buffer[BUFFERSIZE];
static Brick bricks[NMAX];

inline char get_valid_char() {
    char c = getchar();

    while (!isalnum(c))
        c = getchar();

    return c;
}

int main() {
    scanf("%d", &q);

    while (q--) {
        char command = get_valid_char();

        switch (command) {
            case 'A': {
                int x;
                scanf("%s%d", buffer, &x);

                Brick &dest = bricks[x];
                dest.append(buffer);
            } break;

            case 'N': {
                scanf("%s", buffer);

                n++;
                bricks[n].append(buffer);
            } break;

            case 'M': {
                int x, y;
                scanf("%d%d", &x, &y);

                Brick &src = bricks[x];
                Brick &dest = bricks[y];
                dest.append(src);
            } break;

            case 'Q': {
                char c;
                int x;
                c = get_valid_char();
                scanf("%d", &x);

                printf("%d\n", bricks[x].query(c));
            } break;
        }  // switch to command
    }      // while

    return 0;
}  // function main
