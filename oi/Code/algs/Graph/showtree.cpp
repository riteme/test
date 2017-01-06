#include <cstdlib>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    int n;
    cin >> n;

    stringstream buffer;
    buffer << "graph {" << endl;
    buffer << "    node [ shape = circle ];" << endl;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        buffer << "    " << u << " -- " << v << ";" << endl;
    }
    
    buffer << "}" << endl;

    ofstream writer("/tmp/tree.dot");
    writer << buffer.str();
    writer.close();

    system("showdot /tmp/tree.dot &");
    
    return 0;
}
