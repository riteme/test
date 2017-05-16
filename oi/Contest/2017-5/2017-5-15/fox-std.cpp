#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

#define mod 1000000007

const int m = 16;
typedef long long int64;
typedef int64 mat[m][m];

mat unit, ans;

void matmul (mat A, mat B, mat C)
{
  mat t; int i, j, k;
  memset (t, 0, sizeof (t));
  for (i = 0; i < m; ++i)
    for (j = 0; j < m; ++j)
      for (k = 0; k < m; ++k)
        t[i][j] += A[i][k] * B[k][j] % mod;
  for (i = 0; i < m; ++i)
    for (j = 0; j < m; ++j)
      C[i][j] = t[i][j] % mod;
}

int work (int64 n, int S, int L, int R)
{
  int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0}, i, k;
  memset (unit, 0, sizeof (unit));
  for (i = 0; i < 4; ++i)
    {
      int w = (i + 1) & 3;
      for (k = 0; k < 4; ++k)
        unit[i * 4 + k][i * 4 + k] = S, unit[i * 4 + k][w * 4 + k] = L, unit[w * 4 + k][i * 4 + k] = R;
      unit[i * 4 + 0][i * 4 + 1] += (mod + dy[i] * S) % mod;
      unit[i * 4 + 0][i * 4 + 2] += (mod + dx[i] * S) % mod;
      unit[i * 4 + 1][i * 4 + 3] += (mod + dx[i] * S) % mod;
      unit[i * 4 + 2][i * 4 + 3] += (mod + dy[i] * S) % mod;
    }

  memset (ans, 0, sizeof (ans));
  ans[0][0] = 1;
  for (i = 0; n && i < 8; ++i, --n)
    matmul (ans, unit, ans);
  for (; n; n >>= 1, matmul (unit, unit, unit))
    n & 1 ? matmul (ans, unit, ans), 0 : 0;
  int64 t = 0;
  for (i = 0; i < 4; ++i)
    t += ans[0][i * 4 + 3];
  return t % mod;
}

class SplittingFoxes {
public:
  int sum(long long n, int S, int L, int R) {
    return work (n, S, L, R);
  }
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    for (; T--; ) {
        int64 t; int S, L, R;
        cin >> t >> S >> L >> R;
        SplittingFoxes *x = new SplittingFoxes;
        cout << x->sum(t, S, L, R) << endl;
    }
    return 0;
}
