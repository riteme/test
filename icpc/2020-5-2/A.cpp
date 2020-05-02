#include <cstdio>
#include <cstring>

#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define NMAX 100000

struct Block {
    int size;
    bool avail;
    Block *next;
};

static Block mem[2 * NMAX];
Block *require() {
    static size_t mempos = 0;
    auto r = mem + mempos;
    mempos++;
    return r;
}

unordered_map<string, int> var;
Block *head;

void gc() {
    for (auto x = head; x; x = x->next) if (x->avail) {
        while (x->next && x->next->avail) {
            x->size += x->next->size;
            x->next = x->next->next;
            // delete x->next;
        }
    }
}

int allocate(int len) {
    gc();

    int ptr = 1;
    for (auto x = head; x; x = x->next) {
        if (x->avail && x->size >= len) {
            x->avail = false;
            if (x->size > len) {
                auto z = require();
                z->size = x->size - len;
                z->avail = true;
                z->next = x->next;

                x->size = len;
                x->next = z;
            }
            return ptr;
        } else
            ptr += x->size;
    }

    return 0;
}

void release(int ptr) {
    if (!ptr)
        return;

    int cur = 1;
    for (auto x = head->next; x; x = x->next) {
        if (cur == ptr) {
            x->avail = true;
            return;
        } else
            cur += x->size;
    }
}

int main() {
    head = require();
    head->next = require();
    head->next->avail = true;
    head->next->size = NMAX;

    int n;
    scanf("%d", &n);
    char s[256];
    while (n--) {
        scanf("%s", s);
        int l, r;
        for (int i = 0; s[i]; i++) {
            if (s[i] == '(')
                l = i;
            if (s[i] == ')')
                r = i;
        }
        s[r] = 0;
        string arg = s + l + 1;

        if (s[4] == '=') {
            s[4] = 0;
            string name = s;
            int size = atoi(arg.c_str());
            var[name] = allocate(size);
        } else if (s[0] == 'f') {
            int ptr = var[arg];
            release(ptr);
            var[arg] = 0;
        } else
            printf("%d\n", var[arg]);
    }

    return 0;
}