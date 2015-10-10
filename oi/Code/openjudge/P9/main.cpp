// easy
#include <iostream>
#include <set>

using namespace std;

int main(/*int argc, char *argv[]*/) {
    cout.sync_with_stdio(false);

    set<int> numbers;
    int n;

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int tmp;
        cin >> tmp;

        numbers.insert(tmp);
    }  // for

    cout << numbers.size() << endl;
    for (set<int>::iterator beg = numbers.begin(); beg != numbers.end(); beg++) {
        cout << *beg << (beg != --numbers.end() ? " " : "");
    }  // for
    cout << endl;

    return 0;
}  // function main
