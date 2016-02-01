#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define NMAX 1000

struct Edge {
    int from;
    int to;
    int capacity;
    int cost;
    Edge *reverse_edge;
};  // struct Edge

#ifdef TEST
#include <iostream>
using std::cin;
using std::cout;
#else
static auto cin = ifstream("airl.in");
static auto cout = ofstream("airl.out");
#endif  // IFDEF TEST

static unordered_map<string, int> name_map;
static int n, m;
static vector<Edge *> G[NMAX + 10];

inline void add_edge(int u, int v, int capacity, int cost) {
    Edge *e = new Edge();
    Edge *re = new Edge();

    e->from = u;
    e->to = v;
    e->capacity = capacity;
    e->cost = -cost;

    re->from = v;
    re->to = v;
    re->capacity = 0;
    re->cost = cost;

    e->reverse_edge = re;
    re->reverse_edge = e;

    G[u].push_back(e);
    G[v].push_back(re);
}

void initialize() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        string name;
        cin >> name;
        name_map[name] = i;
    }  // for
}

int main() {
    initialize();

    return 0;
}  // function main
