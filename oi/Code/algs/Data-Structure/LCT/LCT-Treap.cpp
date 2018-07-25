#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

using namespace std;

#define SEED (577777777)

static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;

#define LCTSIZE 1000

struct LCT {
    struct Treaps {
        void reset(int n) {
            memset(father, 0, sizeof(int) * (n + 1));
            memset(left, 0, sizeof(int) * (n + 1));
            memset(right, 0, sizeof(int) * (n + 1));
            memset(reversed, 0, sizeof(bool) * (n + 1));
            
            for (int i = 1; i <= n; i++)
                weight[i] = randint();
        }

        int father[LCTSIZE + 10];
        int left[LCTSIZE + 10];
        int right[LCTSIZE + 10];
        int weight[LCTSIZE + 10];
        bool reversed[LCTSIZE + 10];
    };
};
