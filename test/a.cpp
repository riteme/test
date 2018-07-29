#include <iostream>
#include <map>

using namespace std;

int main() {
    cout << sizeof(map<long long, long long>::node_type) << endl;
    cout << sizeof(_Rb_tree_node_base) << endl;
    return 0;
}
