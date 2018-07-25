// #define USE_FILE_IO
// #define NDEBUG

#define NAME "bipartite"

#include <cassert>
#include <cstdio>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

class UnionFind {
 public:
    UnionFind() {
        memset(set, 0, sizeof(set));
        for (int i = 1; i <= NMAX; i++) {
            size[i] = 1;
        }
    }

    int find(int u) {
        return set[u] ? find(set[u]) : u;
    }

    void link(int u, int v) {
        assert(!set[u]);
        assert(!set[v]);

        if (size[u] < size[v])
            swap(u, v);

        set[v] = u;
        size[u] += size[v];
    }

    void remove(int u, int v) {
        if (set[u] != v)
            swap(u, v);

        assert(set[u] == v);

        while (v) {
            size[v] -= size[u];
            v = set[v];
        }
        set[u] = 0;
    }

 private:
    int set[NMAX + 10];
    int size[NMAX + 10];
};

class Solver {
 public:
    Solver() : answer(true), cnt(0) {
        memset(match, 0, sizeof(match));
    }

    void add(int u, int v) {
        if (!answer) {
            cnt++;
            return;
        }

        int idu = uf.find(u);
        int idv = uf.find(v);

        if (idu == idv) {
            answer = false;
            cnt = 1;
            return;
        }

        op.push(nullptr);

        if (match[idu] == idv)
            return;

        if (match[idv]) {
            uf.link(idu, match[idv]);
            op.push(new RemoveCommand(this, idu, match[idv]));
        }

        if (match[idu]) {
            uf.link(match[idu], idv);
            op.push(new RemoveCommand(this, match[idu], idv));
        }

        int nidu = uf.find(idu);
        int nidv = uf.find(idv);
        op.push(new ModifyCommand(this, nidu, match[nidu]));
        op.push(new ModifyCommand(this, nidv, match[nidv]));
        match[nidu] = nidv;
        match[nidv] = nidu;
    }

    void ret() {
        if (cnt > 1)
            cnt--;
        else if (cnt == 1) {
            answer = true;
            cnt = 0;
        } else {
            while (true) {
                Command *command = op.top();
                op.pop();

                if (command == nullptr)
                    break;

                command->execute();
            }
        }
    }

    bool answer;

 private:
    struct Command {
        virtual void execute() = 0;
    };

    struct RemoveCommand : public Command {
        RemoveCommand(Solver *_target, int _u, int _v)
            : target(_target), u(_u), v(_v) {}

        Solver *target;
        int u, v;

        virtual void execute() {
            target->uf.remove(u, v);
        }
    };

    struct ModifyCommand : public Command {
        ModifyCommand(Solver *_target, int _u, int _v)
            : target(_target), u(_u), v(_v) {}

        Solver *target;
        int u, v;

        virtual void execute() {
            target->match[u] = v;
        }
    };

    stack<Command *> op;
    UnionFind uf;
    int match[NMAX + 10];
    int cnt;
};

static int n, q;
static Solver solver;

void initialize() {
    scanf("%d%d", &n, &q);
}

int main() {
    freopen(NAME ".in", "r", stdin);
#ifdef USE_FILE_IO
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    initialize();

    char command[8];
    while (q--) {
        scanf("%s", command);

        if (command[0] == 'A') {  // ADD u v
            int u, v;
            scanf("%d%d", &u, &v);
            solver.add(u, v);
        } else {  // RETURN
            solver.ret();
        }

        puts(solver.answer ? "YES" : "NO");
    }

    return 0;
}
