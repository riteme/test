#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 400000

static int n;
static char buffer[BUFFERSIZE];

static void initialize() {
    scanf("%d%s", &n, buffer);
}

struct State {
    State() : length(0), suffix_link(NULL) {
        memset(transition, 0, sizeof(transition));
    }

    int length;
    State *suffix_link;
    State *transition[26];
};  // struct State

static State *build_suffix_automaton() {
    State *first = new State;
    State *last = first;

    for (unsigned pos = 0; buffer[pos] != '\0'; pos++) {
        unsigned chr = buffer[pos] - 'a';
        State *next = new State;
        State *x = last;

        while (x && x->transition[chr] == NULL) {
            x->transition[chr] = next;
            x = x->suffix_link;
        }  // while

        if (!x)
            next->suffix_link = first;
        else {
            if (x->length + 1 != x->transition[chr]->length) {
                State *target = x->transition[chr];
                State *newstate = new State;

                next->suffix_link = newstate;
                *newstate = *target;
                newstate->suffix_link = target->suffix_link;
                target->suffix_link = newstate;
                newstate->length = x->length + 1;

                while (x && x->transition[chr] == target) {
                    x->transition[chr] = newstate;
                    x = x->suffix_link;
                }  // while
            } else
                next->suffix_link = x->transition[chr];
        }

        next->length = last->length + 1;
        last = next;
    }  // for

    return first;
}

static int walked = 0;
static void greedy(State *x) {
    for (unsigned p = 0; p < 26; p++) {
        if (x->transition[p]) {
            walked++;
            greedy(x->transition[p]);
            break;
        }
    }  // for
}

int main() {
    freopen("MinRepresentations.in", "r", stdin);
    freopen("MinRepresentations.out", "w", stdout);
    initialize();

    State *m = build_suffix_automaton();
    greedy(m);

    // printf("%d\n", walked);
    for (int i = n - walked; i < n; i++) {
        putchar(buffer[i]);
    }  // for
    for (int i = 0; i < n - walked; i++) {
        putchar(buffer[i]);
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
