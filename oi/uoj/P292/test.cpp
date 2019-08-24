#include <bitset>
#include <iostream>
#include <algorithm>

using namespace std;

#define BITSET_SIZE 10000

typedef bitset<BITSET_SIZE> Bitset;

int main() {
    ios::sync_with_stdio(false);
    Bitset poly;
    cin >> poly;
    int K;
    while (cin >> K) {
        Bitset ret(1);
        while (K--) {
            Bitset tmp;
            for (int i = 0; i < poly.size(); i++)
                if (poly[i]) tmp ^= ret << i;
            ret = tmp;
        }
        int i = ret.size() - 1;
        for (; !ret[i]; i--) ;
        for (; i >= 0; i--) putchar(ret[i] ? '1' : '0');
        putchar('\n');
    }
    return 0;
}
