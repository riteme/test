#include <cstdio>
#include <cstring>

#include <algorithm>
#include <iterator>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef unsigned long long uint64;

static unordered_map<uint64, uint64> memorize;

static uint64 evaluate(uint64 x) {
    if (x == 0)
        return 0;
    if (x == 1)
        return 1;
    if (memorize.count(x))
        return memorize[x];

    uint64 result = evaluate(x >> 1);

    if (x & 1)
        result += evaluate((x >> 1) + 1);

    memorize[x] = result;
    return result;
}

map<uint64, uint64> seq;

static void generate(uint64 n) {
    seq[1] = 1;
    unordered_set<uint64> marked;
    priority_queue<uint64, vector<uint64>, greater<uint64>> q;
    q.push(1);

    while (!q.empty()) {
        uint64 u = q.top();
        marked.insert(u);
        q.pop();

        bool avaliable = false;
        uint64 result = evaluate(u);
        if (u == 1)
            avaliable = true;
        else if (result > seq.rbegin()->second) {
            seq[u] = result;
            avaliable = true;
        }

        if (avaliable) {
            if (!marked.count((u << 1) - 1) && (u << 1) - 1 <= n)
                q.push((u << 1) - 1);
            if (!marked.count((u << 2) - 1) && (u << 2) - 1 <= n)
                q.push((u << 2) - 1);
        }
    }
}

int main() {
    generate(2000000000000000000);

    int t;
    scanf("%d", &t);

    while (t--) {
        uint64 n;
        scanf("%llu", &n);

        auto iter = seq.lower_bound(n);

        if (iter->first > n)
            iter = prev(iter);

        printf("%llu\n", iter->second);
    }  // while

    return 0;
}  // function main
