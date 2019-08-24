// 编辑距离问题

// 插入操作与删除操作可以互换，为简便计算将插入视为删除
// f[i][j]: 子串a[1..i]与子串b[1..j]的编辑距离
// 则：
// f[0][0] = 0, 无需对齐
// f[0][j] = f[j][0] = j, 只能依靠删除j个字符来对齐
// f[i][j] = min{f[i - 1][j] + 1,  删除a子串的一个字符
//               f[i][j - 1] + 1,  删除b子串的一个字符
//               f[i - 1][j - 1] + g(i, j)  将最后一个字符进行替换操作
//              }
//  注：
//  g(i, j): 如果a[i]与b[j]相同，表示此处无需替换，返回0
//           否则返回1

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_LENGTH 4000

static string a, b;
static int f[MAX_LENGTH + 10][MAX_LENGTH + 10];

void initialize();
void output();

inline int is_equal(int i, int j) { return a[i - 1] == b[j - 1] ? 0 : 1; }

int main() {
    ios::sync_with_stdio(false);
    initialize();

    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            f[i][j] = min(min(f[i - 1][j] + 1, f[i][j - 1] + 1),
                          f[i - 1][j - 1] + is_equal(i, j));
        }  // for
    }      // for

    output();
    return 0;
}  // function main

void initialize() {
    cin >> a >> b;

    f[0][0] = 0;

    for (int i = 1; i <= MAX_LENGTH; i++) {
        f[0][i] = i;
        f[i][0] = i;
    }  // for
}

void output() { cout << f[a.size()][b.size()]; }
