#include <cassert>

#include <string>
#include <iostream>

#include "int2048_t.hpp"

using std::cout;
using std::endl;
using std::string;

uint64_t int2048_t::cost;

inline string bin(const int x) {
    string s;

    for (int i = 30; i >= 0; i--)
        s.push_back('0' + ((x >> i) & 1));

    return s;
}

#define NUMBER(x) (int2048_t(bin(x)))
#define BINARY(x) (int2048_t(x))

int main() {
    assert(int2048_t("110") == NUMBER(6));
    
    assert(NUMBER(1) + NUMBER(2) == NUMBER(3));
    assert(NUMBER(9) + NUMBER(99) == NUMBER(108));
    assert(-NUMBER(121) + NUMBER(120) == -NUMBER(1));

    assert(-(-NUMBER(2333)) == NUMBER(2333));

    assert(NUMBER(9) - NUMBER(6) == NUMBER(3));
    assert(NUMBER(9) - NUMBER(12) == -NUMBER(3));
    assert(NUMBER(101) - NUMBER(2) == NUMBER(99));
    assert(NUMBER(0) - NUMBER(7) == -NUMBER(7));
    assert(-NUMBER(12) - NUMBER(12) == -NUMBER(24));

    assert(~BINARY("010"));

    assert((NUMBER(2) & NUMBER(8)) == NUMBER(0));
    assert((NUMBER(4) & NUMBER(5)) == NUMBER(4));

    assert((NUMBER(2) | NUMBER(8)) == NUMBER(10));
    assert((NUMBER(4) | NUMBER(5)) == NUMBER(5));

    assert((NUMBER(2) ^ NUMBER(8)) == NUMBER(10));
    assert((NUMBER(4) ^ NUMBER(5)) == NUMBER(1));
    
    assert((NUMBER(2) << 4) == NUMBER(32));
    assert((NUMBER(9) << 5) == NUMBER(288));

    assert((NUMBER(65536) >> 3) == NUMBER(8192));
    assert((NUMBER(1023) >> 4) == NUMBER(63));

    assert(NUMBER(233) == NUMBER(233));
    assert(NUMBER(233) != -NUMBER(233));
    assert(NUMBER(0) == -NUMBER(0));

    assert(NUMBER(2) < NUMBER(3));
    assert(-NUMBER(100) < NUMBER(1));
    assert(-NUMBER(100) < -NUMBER(99));
    assert(NUMBER(0) < -NUMBER(0) == false);

    assert(NUMBER(666) > NUMBER(233));
    assert(-NUMBER(666) > -NUMBER(667));
    assert(NUMBER(0) > -NUMBER(1));
    assert(-NUMBER(12) > NUMBER(6) == false);

    assert(NUMBER(13) <= NUMBER(13));
    assert(-NUMBER(13) <= NUMBER(13));

    assert(NUMBER(6666) >= NUMBER(6666));
    assert(NUMBER(6666) >= -NUMBER(6667));

    assert(NUMBER(123));
    assert(!NUMBER(0));
    assert((bool) NUMBER(123124) == true);
    assert(bool(NUMBER(0)) == false);
    assert(static_cast<bool>(-NUMBER(0)) == false);
    assert((bool) -NUMBER(123) == true);

    cout << "exCited!" << endl;

    return 0;
}
