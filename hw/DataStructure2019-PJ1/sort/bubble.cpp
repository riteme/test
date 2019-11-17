#include "protocol.h"

#include <algorithm>

using namespace std;

extern int n;
extern Pack s[500];

void sort() {
    for (int i = 0; i < 1000; i++)
    for (int j = 2; j <= n; j++)
        if (s[j] < s[j - 1]) swap(s[j - 1], s[j]);
}
