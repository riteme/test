#include <bits/stdc++.h>

using namespace std;

#define NMAX 250000

static vector<int> T[NMAX + 10];
static int id[NMAX * 2 + 10];
static int seq[NMAX * 2 + 10], t;

void dfs(int x) {
    seq[t++] = x;
    for (int v : T[x]) {
        dfs(v);
        seq[t++] = x;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) return fprintf(stderr, "Usage: %s [T] [n]\n", argv[0]), -1;
    int Tc = atoi(argv[1]);
    int n = atoi(argv[2]);
    for (int i = 1; i <= 2 * n; i++) id[i] = i;
    printf("%d\n", Tc);
    while (Tc--) {
        srand(random_device()());
        for (int i = 1; i <= n; i++) T[i].clear();
        for (int v = 2; v <= n; v++) T[rand() % (v - 1) + 1].push_back(v);
        t = 1;
        dfs(1);
        random_shuffle(id + 1, id + 2 * n);
        int L = rand() % (2 * n);
        for (int i = 1; i <= L; i++) seq[id[i]] = 0;
        printf("%d\n", n);
        for (int i = 1; i <= 2 * n - 1; i++) printf("%d ", seq[i]);
        puts("");
    }

    return 0;
}
