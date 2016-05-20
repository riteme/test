#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define LOGN 21

static int n, m;
static int a[NMAX + 10];
static int f[NMAX + 10][LOGN + 1];

static void compute_st() {}
