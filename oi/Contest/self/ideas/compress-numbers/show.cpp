#include <cstdio>
#include <cstdlib>

#include <sstream>
#include <fstream>

using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    stringstream buffer;
    buffer << "digraph {node [shape = circle];";

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        buffer << u << "->" << v << "[label = \"" << w << "\"];";
    }

    buffer << "}";

    ofstream writer("/tmp/graph.dot");
    writer << buffer.str();
    writer.close();

    system("showdot /tmp/graph.dot");

    return 0;
}  // function main
