#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <cctype>

#define BUFFERSIZE 65536
static size_t pos = BUFFERSIZE;
static char buffer[BUFFERSIZE];

inline char _getchar() {
    if (pos == BUFFERSIZE) {
        pos = 0;
        fread(buffer, 1, BUFFERSIZE, stdin);
    }
    return buffer[pos++];
}

inline int readint() {
    int x = 0;
    char c = _getchar();

    while (!isdigit(c)) {
        c = _getchar();
    }

    while (isdigit(c)) {
        x = x * 
    }
}
