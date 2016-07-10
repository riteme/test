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
    State() : id(0), length(0), suffix_link(NULL) {
        memset(transitions, NULL, sizeof(transitions));
    }

    int id;
    int length;
    State *suffix_link;
    State *transitions[SIGMA];
};  // struct State

static State *build_suffix_automaton(const char *buffer) {
    static int idcnt = 0;
    State *first = new State;  // empty string suffix automaton
    State *last = first;

    for (unsigned p = 0; buffer[p] != '\0'; p++) {
        char chr = buffer[p];
        printf("Constructing %c...\n", chr);

        // Construct new state
        State *nxt = new State;

        // Add transitions for each acceptable states
        // Find the first one who has transition on `chr`
        State *x = last;
        while (x && x->transitions[chr] == NULL) {
            x->transitions[chr] = nxt;
            x = x->suffix_link;
        }  // while

        // When x is nullptr, we reached the head of automaton
        if (!x)
            nxt->suffix_link = first;
        else {
            // x now point to the last one who has the `chr` transition
            if (x->length + 1 != x->transitions[chr]->length) {
                puts("233");
                State *target = x->transitions[chr];
                State *newstate = new State;

                // Setup next's suffix link
                nxt->suffix_link = newstate;

                // Copy the target state
                *newstate = *target;
                newstate->id = ++idcnt;

                // Reset suffix links
                newstate->suffix_link = target->suffix_link;
                target->suffix_link = newstate;

                // `newstate` is `x`'s neighbor
                newstate->length = x->length + 1;

                // Reset transitions
                while (x && x->transitions[chr] == target) {
                    x->transitions[chr] = newstate;
                    x = x->suffix_link;
                }  // while
            } else
                nxt->suffix_link = x->transitions[chr];
        }

        // Reset last state
        nxt->id = ++idcnt;
        nxt->length = last->length + 1;
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

    buffer << x->id << "[label=\"" << x->length << "\"];";
    for (unsigned c = 0; c < SIGMA; c++) {
        if (x->transitions[c] != NULL)
            buffer << x->id << "->" << x->transitions[c]->id << "[label=\""
                   << char(c) << "\" style=bold];";
    }  // for
    // if (x->suffix_link)
    //     buffer << x->id << "->" << x->suffix_link->id << "[style=dashed];";
    // else
    //     buffer << x->id << "->" << x->id << "[style=dashed];";

    for (unsigned c = 0; c < SIGMA; c++) {
        if (x->transitions[c] != NULL)
            print(x->transitions[c], buffer);
    }  // for
}

static void show(State *x) {
    stringstream buffer;
    buffer << "digraph{ordering=out;node[shape=circle];";

    State *y = x;
    buffer << "{rank=same;";
    buffer << y->id << ";";
    for (unsigned p = 0; data[p] != '\0'; p++) {
        y = y->transitions[data[p]];
        buffer << y->id << ";";
    }  // for
    buffer << "}";

    memset(marked, false, sizeof(marked));
    print(x, buffer);

    buffer << "}";

    ofstream file("/tmp/suffixautomata.tmp.dot");
    file << buffer.str();
    file.close();
    system("showdot /tmp/suffixautomata.tmp.dot -dot &");
}

int main() {
    while (scanf("%s", data) != EOF) {
        State *m = build_suffix_automaton(data);
        show(m);
    }  // while

    return 0;
}  // function main
