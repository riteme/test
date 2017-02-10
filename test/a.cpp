#include <cassert>
#include <cstring>

#include <random>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

#define BUFFERSIZE 20000000
#define MAX_DISTANCE 5000000

typedef unsigned char u8;

static random_device rd;
static u8 memory[BUFFERSIZE];

inline u8 randchr() {
    return rd() % 255 + 1;
}

inline int randint(int l, int r) {
    return rd() % (r - l + 1) + l;
}

inline u8 *strend(u8 *s) {
    while (*s)
        s++;

    return s;
}

int main() {
    for (size_t i = 0; i < BUFFERSIZE; i++) 
        memory[i] = randchr();
    memory[randint(BUFFERSIZE - MAX_DISTANCE, BUFFERSIZE)] = 0;

    steady_clock clock;
    u8 *ret1, *ret2, *ret3, *ret4;

    auto beg = clock.now();
    ret1 = (u8 *) memchr(memory, 0, sizeof(memory));
    auto now = clock.now();
    long long span = duration_cast<nanoseconds>(now - beg).count();
    cout << "memchr: " << span << "ns" << endl;

    this_thread::sleep_for(seconds(1));

    beg = clock.now();
    ret2 = (u8 *) rawmemchr(memory, 0);
    now = clock.now();
    span = duration_cast<nanoseconds>(now - beg).count();
    cout << "rawmemchr: " << span << "ns" << endl;

    this_thread::sleep_for(seconds(1));

    beg = clock.now();
    ret3 = memory + strlen((char *) memory);;
    now = clock.now();
    span = duration_cast<nanoseconds>(now - beg).count();
    cout << "strlen: " << span << "ns" << endl;

    this_thread::sleep_for(seconds(1));

    beg = clock.now();
    ret4 = strend(memory);;
    now = clock.now();
    span = duration_cast<nanoseconds>(now - beg).count();
    cout << "my impl: " << span << "ns" << endl;

    assert(ret1 == ret2 &&
           ret2 == ret3 &&
           ret3 == ret4);

    return 0;
}
