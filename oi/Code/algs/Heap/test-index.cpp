//
// Copyright 2015 riteme
//

#include "IndexPriorityQueue.hpp"

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    IndexPriorityQueue<int> q(n);

    char command;
    while (cin >> command) {
        switch (command) {
            case 'S': cout << q.Size() << endl; break;
            case 'P': {
                int index, value;
                cin >> index >> value;

                q.Push(index, value);
            } break;
            case 'T': cout << q.Top() << endl; break;
            case 'F': q.Pop(); break;
            case 'D': {
                int index, value;
                cin >> index >> value;
                q.Decrease(index, value);
            } break;
            case 'I': {
                int index, value;
                cin >> index >> value;
                q.Increase(index, value);
            } break;
            case 'Q': {
                int index;
                cin >> index;

                cout << boolalpha << q.IsExist(index) << endl;
            }
        }  // switch to command
    }      // while

    return 0;
}  // function main
