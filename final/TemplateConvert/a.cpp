//
// Copyright 2015 riteme
//

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;

template<typename TReturn>
TReturn Convert(void *value) {
    // return *dynamic_cast<TReturn*>(value);
    return *reinterpret_cast<TReturn*>(value);
}

int main(int argc, char **argv) {
    int a = 0, b = 1, c = 2;
    string s = "Hello, world!";
    void *ps = &s;
    string new_s = Convert<string>(ps);
    void *pa = &a;
    int d = Convert<int>(pa);

    cout << "d: " << d << endl;
    cout << "new_s: " << new_s << endl;
    return 0;
}  // function main
