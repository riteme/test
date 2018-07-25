//
// Copyright 2015 riteme
//

#include <iostream>

using namespace std;

typedef FILE *FilePtr;

class StreamRedirect {
 public:
    StreamRedirect(const std::string &in, const std::string &out) {
        if (!in.empty()) { freopen(in.data(), "r", stdin); }
        if (!out.empty()) { freopen(out.data(), "w", stdout); }
    }
    ~StreamRedirect() {
        fclose(stdin);
        fclose(stdout);
    }
};

int Convert(int n, int m, int result = 0, int pos = 1);

int main() {
    // auto io=StreamRedirect("transformation.in","transformation.out");

    int n, m;
    while (cin >> n >> m) { cout << Convert(n, m) << endl; }  // while

    return 0;
}  // function main

/**
 * 一个M进制的数可表示为：
 * numM(abcd) = a *( M ^ 3) + b * (M ^ 2) + c * M + d
 * 处理流程：
 * n % M = d
 * n - d = a * (M ^ 3) + b * (M ^ 2) + c * M
 * 将每一位数都降位
 * n / M = a * (M ^ 2) + b * M + c
 * 此时
 * n % M = c
 * 按照以上流程即可取得M进制数的每一位
 * 缺点：是逆序取得的...
 * @param  n      某进制数
 * @param  m      目标进制
 * @param  result （用于递归）保存结果
 * @param  pos    （用于递归）保存位置，方便把新取得的数字放到开头
 * @return        转换后的数字
 */
int Convert(int n, int m, int result, int pos) {
    // 如果n被处理完了，n应当等于0
    if (n == 0) { return result; }

    // 按照新进制取得最后一位
    auto digit = n % m;

    // 将得到的数字放到开头
    result = digit * pos + result;

    // 左翼位置
    pos *= 10;

    // 减去最后一位，并将数字右移
    n = (n - digit) / m;

    // 如此反复...
    return Convert(n, m, result, pos);  // 尾递归不会爆栈
}
