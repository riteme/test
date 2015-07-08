#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <typename Iter, typename T>
Iter Find(Iter beg, Iter end, const T &value) {
    for (; beg != end; ++beg) {
        if (*beg == value) {
            break;
        }
    }
    return beg;
}

int main(int argc, char **argv) {
    vector<string> vec = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    /* cout << *Find(vec.begin(), vec.end(), "2") << endl; */
    auto iter = Find(vec.begin(), vec.end(), "3");
    cout << *iter << endl;
}
