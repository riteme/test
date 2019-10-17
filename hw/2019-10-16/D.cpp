#include <cstdio>
#include <cctype>
#include <cstring>

#define gc getchar

#define LIMIT 80
#define BUFSIZE 1024
#define SEPARATER "--------------------------------------------------------------------------------"

enum Token {
    TK_UNKNOWN,
    TK_EOF,
    TK_SPACE,
    TK_WORD,
    TK_TAG
};

static Token tk = TK_UNKNOWN;
static char literal[BUFSIZE];
static int tail = 0;
bool next() {
    static char c = gc();
    tail = 0;
    if (c == EOF) {
        tk = TK_EOF;
        return false;
    } else if (isspace(c)) {
        tk = TK_SPACE;
        do {
            c = gc();
        } while (isspace(c));
    } else if (c == '<') {
        tk = TK_TAG;
        for (c = gc(); c != '>'; c = gc()) {
            if (isgraph(c)) literal[tail++] = c;
        }
        c = gc();  // skip '>'
    } else {
        tk = TK_WORD;
        do {
            literal[tail++] = c;
            c = gc();
        } while (isgraph(c));
    }
    literal[tail] = 0;
    //fprintf(stderr, "%d: \"%s\"\n", tk, literal);
    return true;
}

int main() {
    Token last = TK_UNKNOWN;
    int i = 0;
    while (next()) {
        switch (tk) {
            case TK_SPACE: {
                if (last != TK_UNKNOWN) {
                    last = TK_SPACE;
                }
            } break;
            case TK_TAG: {
                if (literal[0] == 'b') {
                    puts("");
                } else if (literal[0] == 'h') {
                    if (i) puts("");
                    puts(SEPARATER);
                }
                i = 0;
                last = TK_UNKNOWN;
            } break;
            case TK_WORD: {
                int len = tail;
                if (last == TK_SPACE) len += 1;
                if (i + len > LIMIT) {
                    puts("");
                    i = 0;
                    last = TK_UNKNOWN;
                }
                len = tail;
                if (last == TK_SPACE) {
                    putchar(' ');
                    len += 1;
                }
                printf("%s", literal);
                i += len;
                last = TK_WORD;
            } break;
        }
    }
    puts("");
    return 0;
}
