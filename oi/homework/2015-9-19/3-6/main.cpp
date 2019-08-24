#include <iostream>
#include <cassert>
using namespace std;

unsigned long GetNumberOfKinds(int n, int max);

unsigned long GetNumberOfKinds(int n, int max) {
    //分类讨论
    if (n == 1 || max == 1)  // n=1或m=1时，均只有一种情况
        return 1;
    else if (n < max)  // 当n<m时，q(n,m)=q(n,n)
        return GetNumberOfKinds(n, n);
    else if (n == max)  // 当n=m时，有一种情况为{n}，则q(n,m)=q(n,n-1)+1
        return 1 + GetNumberOfKinds(n, max - 1);
    else  // 当n>m时，尝试将切分中的m都减去，并加上其余的切分
        return GetNumberOfKinds(n, max - 1) + GetNumberOfKinds(n - max, max);
    //缺点：易爆栈
}

int main() {
    int n, m;

    while (cin >> n >> m) { cout << GetNumberOfKinds(n, m) << endl; }  // while

    return 0;
}  // function main
