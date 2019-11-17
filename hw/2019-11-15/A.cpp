// FSX nb!
//
// OP 1:
// * * * * x
// x * * * *
// ⇒ +1
//
// OP 2:
// * * * x *
// * * * * x
// ⇒ ×2

#include <cstdio>

#include <deque>

using namespace std;

typedef long long i64;

static deque<int> L, R;
static i64 M;

int main() {
    scanf("%lld", &M);
    i64 N = 0;
    for (int j = 60, i = 0; j >= 0; j--) {
        if ((M >> j) & 1) {
            i++;
            N++;
            L.push_back(i);
            R.push_front(i);
        }
        if (N && j) {
            i++;
            N <<= 1;
            int u = L.back();
            L.pop_back();
            L.push_back(i);
            L.push_back(u);
            R.push_back(i);
        }
    }

    printf("%zu\n", L.size() + R.size());
    for (int i = 0; i < L.size(); i++)
        printf("%d ", L[i]);
    for (int i = 0; i < R.size(); i++)
        printf("%d ", R[i]);
    puts("");
    return 0;
}
