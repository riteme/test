#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

struct Component {
    vector<int> V;

    auto ToString() -> string {
        ostringstream buffer;

        for (auto v : V) {
            buffer << v << " ";
        }  // foreach in V

        return buffer.str();
    }
};  // struct Component

struct DirectedGraph {
    vector<vector<int>> Data;

    auto GetRelative(int v) -> vector<int> & {
        return Data[v];
    }

    auto Size() const -> unsigned {
        return Data.size();
    }
};  // struct DirectedGraph

void TarjanSCC(DirectedGraph &G, int x, vector<int> &dfn, vector<int> &low,
               vector<bool> &exist, vector<int> &stack, int &cnt,
               vector<Component> &result) {
    // 准备工作
    dfn[x] = low[x] = cnt++;
    exist[x] = true;
    stack.push_back(x);

    for (auto v : G.GetRelative(x)) {
        if (dfn[v] == 0) {  // 如果还未访问，即没有编号
            TarjanSCC(G, v, dfn, low, exist, stack, cnt, result);
            low[x] = min(low[x], low[v]);  // 更新一路上所访问到的最小编号
        } else if (exist[v]) {
            //如果已经在栈中，则表明已存在一个环，
            // 且当前的树链也加入了这个环，形成强联通分量
            low[x] = min(low[v], dfn[v]);
        }
    }  // foreach in G.GetRelative(x)

    // 当dfn[x] == low[x]时，说明x为树根
    if (dfn[x] == low[x]) {
        Component c;
        int u;

        // 找出强联通分量
        do {
            u = stack.back();
            stack.pop_back();
            exist[u] = false;
            c.V.push_back(u);
        } while (u != x);  // do ... while

        result.push_back(c);
    }
}

auto TarjanSCC(DirectedGraph &G, int s) -> vector<Component> {
    vector<int> dfn;
    vector<int> low;
    vector<bool> exist;
    vector<int> stack;
    int cnt = 1;
    vector<Component> result;

    dfn.resize(G.Size() + 1);
    low.resize(G.Size() + 1);
    exist.resize(G.Size() + 1);

    TarjanSCC(G, s, dfn, low, exist, stack, cnt, result);

    return result;
}

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    DirectedGraph G;
    G.Data.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        G.Data[u].push_back(v);
    }  // for

    auto scc = TarjanSCC(G, 1);

    for (auto &e : scc) {
        cout << e.ToString() << endl;
    }  // foreach in scc

    return 0;
}  // function main
