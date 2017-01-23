/**
 * 题目不是很难，但是不注意细节一样挂得很惨。
 * 首先特判m = 1和m = 2的情况
 * 对于m > 2情况，我们发现如果可以匹配，那么B去掉两端之后，
 * 中间的串一定是完全匹配的。
 * 而两端只有字符是匹配的，但重复数必须A >= B
 * 因此可以KMP找出所有中间串的位置，然后判定是否可行
 *
 * 注意long long以及判定是否可行时要注意有两个标准！
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long int64;

struct Block {
    int64 count;
    char chr;

    bool operator==(const Block &b) const {
        return count == b.count && chr == b.chr;
    }

    bool operator!=(const Block &b) const {
        return count != b.count || chr != b.chr;
    }
};  // struct Block

static int n, m;
static Block A[NMAX + 10];
static Block B[NMAX + 10];
static int fail[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%lld-%c", &A[i].count, &A[i].chr);
    }  // for

    for (int i = 1; i <= m; i++) {
        scanf("%lld-%c", &B[i].count, &B[i].chr);
    }  // for
}

int compress(Block *str, int size) {
    int pos = 0;
    str[0].chr = '$';
    for (int i = 1; i <= size; i++) {
        if (str[i].chr == str[pos].chr)
            str[pos].count += str[i].count;
        else
            str[++pos] = str[i];
    }  // for

    return pos;
}

int main() {
    initialize();

    n = compress(A, n);
    m = compress(B, m);

    if (m == 1) {
        int64 answer = 0;

        for (int i = 1; i <= n; i++) {
            if (A[i].chr == B[1].chr && A[i].count >= B[1].count)
                answer += A[i].count - B[1].count + 1;
        }  // for

        printf("%lld\n", answer);
    } else if (m == 2) {
        int answer = 0;

        for (int i = 1; i < n; i++) {
            if (A[i].chr == B[1].chr && A[i + 1].chr == B[2].chr &&
                A[i].count >= B[1].count && A[i + 1].count >= B[2].count)
                answer++;
        }  // for

        printf("%d\n", answer);
    } else {
        fail[2] = 1;
        int j = 1;
        for (int i = 3; i < m; i++) {
            while (j > 1 && B[i] != B[j + 1]) {
                j = fail[j];
            }  // while

            if (B[i] == B[j + 1])
                j++;

            fail[i] = j;
        }  // for

        int answer = 0;

        j = 1;
        for (int i = 2; i < n; i++) {
            while (j > 1 && A[i] != B[j + 1]) {
                j = fail[j];
            }  // while

            if (A[i] == B[j + 1])
                j++;

            if (j == m - 1) {
                if (A[i - j + 1].count >= B[1].count &&
                    A[i - j + 1].chr == B[1].chr &&
                    A[i + 1].count >= B[m].count && A[i + 1].chr == B[m].chr)
                    answer++;

                j = fail[j];
            }
        }  // for

        printf("%d\n", answer);
    }

    return 0;
}  // function main
