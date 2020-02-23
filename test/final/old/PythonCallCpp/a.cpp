//
// Copyright 2015 riteme
//

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

extern "C" {
    /*static*/ int i = 0;
    void add_to_i(int value) {
        i += value;
    }
    int get_i(void) {
        return i;
    }

    int add(int a, int b) {
        return a + b;
    }

    void say_hello(const char *who) {
       cout << "Hello, " << who << "!" << endl;
    }
}
