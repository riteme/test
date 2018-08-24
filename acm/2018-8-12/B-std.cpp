#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#else
#define eprintf(...) ;
#endif

#define sz(x) ((int) (x).size())
#define TASK "colored-dominoes"

const int inf = (int) 1.01e9;
const long long infll = (long long) 1.01e18;
const ld eps = 1e-9;
const ld pi = acos((ld) -1);

void precalc() {
}

const int mod = (int) 1e9 + 7;

int mul(int a, int b) {
  return (long long) a * b % mod;
}

void add(int &a, int b) {
  a += b;
  if (a >= mod) {
    a -= mod;
  }
}

int n, m;

int read() {
  if (scanf("%d%d", &n, &m) < 2) {
    return false;
  }
  return true;
}

map<pair<int, unsigned long long>, int> dp, ndp;

void solve() {
  if (n < m) {
    swap(n, m);
  }
  dp.clear();
  dp[make_pair(0, 1ull << ((1 << m) - 1))] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ndp.clear();
      for (auto it = dp.begin(); it != dp.end(); it++) {
        int who = it->first.first;
        unsigned long long msk = it->first.second;
        int val = it->second;
        for (int t = 0; t < 2; t++) {
          unsigned long long nmsk = 0;
          for (int x = 0; x < (1 << m); x++) {
            if (!(msk & (1ull << x))) {
              continue;
            }
            if (x & (1 << j)) {
              nmsk |= (1ull << (x ^ (1 << j)));
              if (j && !(x & (1 << (j - 1))) && ((who >> (j - 1)) & 1) == t) {
                nmsk |= (1ull << (x ^ (1 << (j - 1))));
              }
            } else {
              if (((who >> j) & 1) == t) {
                nmsk |= (1ull << (x ^ (1 << j)));
              }
            }
          }
          add(ndp[make_pair(who ^ (who & (1 << j)) ^ (t << j), nmsk)], val);
        }
      }
      swap(dp, ndp);
    }
  }
  int res = 0;
  for (auto it = dp.begin(); it != dp.end(); it++) {
    if (it->first.second & (1ull << ((1 << m) - 1))) {
      add(res, it->second);
    }
  }
  printf("%d\n", res);
}

int main() {
  precalc();
#ifdef DEBUG
  assert(freopen(TASK ".in", "r", stdin));
  assert(freopen(TASK ".out", "w", stdout));
#endif
  while (read()) {
    solve();
#ifdef DEBUG
    eprintf("Time %.2f\n", (double) clock() / CLOCKS_PER_SEC);
#endif
  }
  return 0;
}
