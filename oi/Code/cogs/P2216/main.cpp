#include "cstdio"
#include "cstdlib"
#include "iostream"
#include "algorithm"
#include "cstring"
#include "bitset"
#include "queue"

using namespace std;

#define INF 0x3F3F3F3F
#define MAX_SIZE 100005
#define Eps
#define Mod
#define Get(x, a) (x ? x->a : 0)
#define Travel(x) for (typeof(x.begin()) it = x.begin(); it != x.end(); ++it)

inline int Get_Int() {
    int Num = 0, Flag = 1;
    char ch;
    do {
        ch = getchar();
        if (ch == '-')
            Flag = -Flag;
    } while (ch < '0' || ch > '9');
    do {
        Num = Num * 10 + ch - '0';
        ch = getchar();
    } while (ch >= '0' && ch <= '9');
    return Num * Flag;
}

int N, M, Sum;
int Last[26];

char S1[MAX_SIZE], S2[MAX_SIZE];

bitset<MAX_SIZE> Position[26], Ans;

int main() {
    freopen("guess.in", "r", stdin);
    freopen("guess.out", "w", stdout);
    scanf("%s", S1);
    scanf("%s", S2);
    N = strlen(S1);
    M = strlen(S2);
    for (int i = 0; i < N; ++i)
        Ans[i] = Position[S1[i] - 'a'][i] = 1;
    for (int i = 0; i < M; ++i) {
        if (S2[i] == '?')
            continue;
        int Now = S2[i] - 'a';
        Position[Now] >>= i - Last[Now];
        Last[Now] = i;
        Ans &= Position[Now];
    }
    for (int i = 0; i < N - M + 1; ++i)
        if (Ans[i])
            ++Sum;
    printf("%d\n", Sum);
    for (int i = 0; i < N - M + 1; ++i)
        if (Ans[i])
            printf("%d\n", i);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
