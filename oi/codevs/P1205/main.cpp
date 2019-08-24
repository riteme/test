#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    string tmp;
    stack<string> s;
    while (cin >> tmp) { s.push(tmp); }  // while

    while (!s.empty()) {
        cout << s.top() << ' ';
        s.pop();
    }  // while

    return 0;
}  // function main
