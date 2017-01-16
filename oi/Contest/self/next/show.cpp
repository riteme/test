#include <cstdlib>

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    stringstream buffer;
    buffer << "graph" << " {" << endl;
    buffer << "    node [ shape = circle ];" << endl;

    for (int i = 1; i <= n; i++)
        buffer << "    " << i << ";" << endl;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        buffer << "    " << u << " -- " << v << endl;
    }

    buffer << "}" << endl;

    ofstream writer("/tmp/graph.dot");
    writer << buffer.str();
    writer.close();

    system("showdot /tmp/graph.dot &");

    return 0;
}
