#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define INVALID_SAY "They have disappeared."

struct Node {
    int key;
    int value;

};  // struct Node

static int n;

static void initialize() {
    scanf("%d", &n);
}
