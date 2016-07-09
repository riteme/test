#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 2048
#define SIGMA 256

struct State {
    State() : id(0), main_transition('\0'), suffix_link(this) {
        memset(transitions, NULL, sizeof(transitions));
    }

    int id;
    char main_transition;
    State *suffix_link;
    State *transitions[SIGMA];
};  // struct State

static State *build_suffix_automaton(const char *buffer) {
    static int idcnt = 0;
    static int subidcnt = 99;
    State *first = new State;  // empty string suffix automaton
    State *last = first;

    for (unsigned p = 0; buffer[p] != '\0'; p++) {
        char chr = buffer[p];
        printf("Constructing %c...\n", chr);

        // Construct main chain
        State *nxt = new State;

        // Setup suffix link
        // Add transitions for each acceptable states
        // at the same time
        State *x = last;
        do {
            x = x->suffix_link;
            if (x->transitions[chr] != NULL) {
                x = x->transitions[chr];
                break;
            } else {
                // Determine whether to split state
                if (x->suffix_link->transitions[x->main_transition] == x &&
                    x->id - 1 != x->suffix_link->id) {
                    printf("%d, %d\n", x->id, x->suffix_link->id);
                    State *newstate = new State;
                    *newstate = *x;
                    x->suffix_link->transitions[x->main_transition] = newstate;
                    x->suffix_link = newstate;
                    newstate->transitions[chr] = nxt;
                    newstate->id = ++subidcnt;
                    x = newstate;
                } else
                    x->transitions[chr] = nxt;
            }
        } while (x != first);  // do ... while
        nxt->suffix_link = x;

        // Add transition
        last->transitions[chr] = nxt;
        nxt->main_transition = chr;

        // Reset last state
        nxt->id = ++idcnt;
        last = nxt;
    }  // for

    return first;
}

static bool marked[2000];

static char data[BUFFERSIZE];

static void print(State *x, stringstream &buffer) {
    if (marked[x->id])
        return;
    marked[x->id] = true;

    for (unsigned c = 0; c < SIGMA; c++) {
        if (x->transitions[c] != NULL)
            buffer << x->id << "->" << x->transitions[c]->id << "[label=\""
                   << char(c) << "\" style=bold];";
    }  // for
    // buffer << x->id << "->" << x->suffix_link->id << "[style=dashed];";

    for (unsigned c = 0; c < SIGMA; c++) {
        if (x->transitions[c] != NULL)
            print(x->transitions[c], buffer);
    }  // for
}

static void show(State *x) {
    stringstream buffer;
    buffer << "digraph{node[shape=circle];";

    // State *y = x;
    // buffer << "{rank=same;";
    // buffer << y->id << ";";
    // for (unsigned p = 0; data[p] != '\0'; p++) {
    //     y = y->transitions[data[p]];
    //     buffer << y->id << ";";
    // }  // for
    // buffer << "}";

    memset(marked, false, sizeof(marked));
    print(x, buffer);

    buffer << "}";

    ofstream file("/tmp/suffixautomata.tmp.dot");
    file << buffer.str();
    file.close();
    system("showdot /tmp/suffixautomata.tmp.dot =dot &");
}

int main() {
    while (scanf("%s", data) != EOF) {
        State *m = build_suffix_automaton(data);
        show(m);
    }  // while

    return 0;
}  // function main
