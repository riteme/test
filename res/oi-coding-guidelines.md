# OI Coding Guidelines

## 目录

[TOC]

## 前言

这份简单的指南主要是关于以下两个方面：

1.  OI 赛场上 C++ 语言的一些常用技巧和注意事项。
2.  NOI Linux (Ubuntu) 中常用的工具和习惯。

由于大多是我个人的感受，所以后面的内容大家简单看看就好。

## 第一部分：C++ 语言

CCF 已经发了公告[^1]，将要在不久后就会逐步取消 Pascal 和 C 语言。对于使用 Pascal 的同学，需要尽快转到 C++ 上面来，而对于使用 C 语言的同学，我觉得这是不存在的，因为 OI 中鲜有使用一些 C++ 高级特性的场景。

[^1]: http://www.noi.cn/about/rules/744-ccfnoi 

这里我将会写一点一般 OIer 容易忽视的一些 C++ 语法和技巧，希望对你们有用。

### 代码结构

我看过的大部分代码都是下面这个结构：

```c++
// 开头注释，或是一些奇怪的东西

#include <...>
#include <...>
#include <...>
// #include <bits/stdc++.h>: someone may love it.

// 花式宏定义
// 一些简单的函数

struct XXPoint {
	// 某某 struct
};

struct XXTree {
    // 某某数据结构
};

void aaa() {
    // ...
}

inline int bbb() {
    // ...
}

// ...

int main() {
    // 开文件
  	init();
    work();
    return 0;
}
```

至于到底该怎么写，这都是个人的习惯和爱好。这里只是建议每个函数不宜过长，最好不要有超过 20 行的函数，因为这种很长的函数不利于代码调试。

### 空格与空行

通常，很多表达式的中间我们都会打上一个空格，用来凸显运算符的位置。一个很长的表达式没有空间，都是比较难以阅读的。如下面这个表达式：

```c++
x1=-b+sqrt(b*b-4*a*c)/2/a;x2=-b-sqrt(b*b-4*a*c)/(2*a);// 解方程
```

普遍会写成这样：

```c++
x1 = -b + sqrt(b * b - 4 * a * c) / 2 / a;
x2 = -b - sqrt(b * b - 4 * a * c) / (2 * a);  // 注释与代码之间通常也有 1-2 个的空格
```

相比之下，下面这个在代码中就清晰很多。当然，如果你觉得像 `4 * a * c` 这种可以写的和数学公式 $4ac$ 一样紧凑，`4*a*c` 也是可以接受的。打这种空格并不需要花费什么时间，只要多试几次，自然就熟悉了。我们的目的在于希望通过这种习惯性的空格来减少自己检查错误的时间。

空行通常用于分隔两段作用有明显差异的代码块，如两个函数之间、同一个函数的不同步骤之间。这个时候写点注释也是可以的，但是上了考场，由于时间原因，大家普遍不会写注释......

下面这段代码我是随便从 UOJ 上截的一段改的，大家体会一下就好。

```c++
sieve();

for (int i = 1; i <= h; i++)
    if (!(a[1] % pri[i])) p[++tot] = pri[i];

for (int i = 1; i <= n; i++) {
    i64 t = gcd(a[1], a[i]);
    
    if (t == 1) {
    	printf("-1 ");
    	continue;
    }

    bool flag = 1;
    for (int j = 1; j <= tot && 1LL * p[j] * p[j] <= t; j++)
        if (!(t % p[j])){
            printf("%lld ", t / p[j]);
            flag = 0;
            break;
        }

    if (flag)
    	printf("1 ");  // t为质数
  	// 一些人可能喜欢这样：if (flag) printf("1 ");  // t为质数
}
```

如果您是一个热衷于缩行的青少年，上面的话您可以无视......

### 命名习惯

通常普遍为大家所接受的就是使用英文（或简写），而不是拼音甚至是拼音简写。我见过一个比较极端的例子就是 `ksm`。乍一看不知道是个什么东西，知道看了代码才知道是 “快速幂” 的意思......一般这种函数通常都会写做 `quick_pow` 或者是 `qpow`。当然，上面的结论是基于方便他人理解你的代码而得出的。在 OI 中，基本没人会在意你是怎么写的。所以如果你更熟悉我们的国语，使用拼音命名法也无妨。

兼顾阅读效率和编码效率，我的推荐是名称最好是 2-4 个字符，超过 6 个字符是不太适合的。之所以不推荐 1 个字符，是因为容易产生命名冲突，也容易写错代码。

下面列举了一些在 OI 中常见的写法及其含义：

|              写法              |         原始单词 / 符号         |                   注释                   |
| :--------------------------: | :-----------------------: | :------------------------------------: |
|            `aha`             |           Aha!            |            dalao HJWJBSR 最爱            |
|            `ans`             |          answer           |                                        |
|            `arr`             |           array           |                                        |
|            `buc`             |          bucket           |                 桶排序相关                  |
|            `buf`             |          buffer           |                 缓存、缓冲                  |
|             `ch`             |     child / children      |                通常指树上的儿子                |
|            `chk`             |           check           |                                        |
|            `cls`             |           clear           |               貌似来源于一个命令                |
|        `cmp`, `comp`         |          compare          |            想必你在 `sort` 中用过             |
|            `cnt`             |           count           |                                        |
|            `cur`             |          current          |                                        |
|            `del`             |          delete           |                                        |
|        `dist`, `dis`         |         distance          |                                        |
|            `div`             |          divisor          |                   因子                   |
|            `div`             |          divide           |                   除法                   |
|           `e`, `E`           | $\mathrm{e} = 2.71828...$ |               自然对数函数的底数                |
|         `eps`, `EPS`         |  $\varepsilon$ (epsilon)  |             通常表示精度设定（浮点数中）             |
|            `equ`             |           equal           |                                        |
|            `err`             |           error           |                                        |
|            `eval`            |         evaluate          |                   计算                   |
|            `expr`            |        expression         |                  表达式                   |
|        `f`, `g`, `dp`        |             -             |               一般的 DP 数组                |
|             `fa`             |          father           |                                        |
|            `func`            |         function          |                   函数                   |
|           `g`, `G`           |   graph / primive root    |               图 / 数论中的原根               |
|        `i`, `j`, `k`         |             -             |                  各种下标                  |
|         `inf`, `INF`         |         infinity          |       `#define INF 0x3f3f3f3f`?        |
|            `init`            |        initialize         |                                        |
|            `ins`             |          insert           |                                        |
|           `interp`           |        interpolate        | 线性插值，$\vec c = (1-t)\vec a + t \vec b$ |
|            `inv`             |          inverse          |                   逆元                   |
| `iX` `(X = 16, 32, 64, 128)` |      signed integer       |                 有符号整型                  |
|            `jmp`             |           jump            |                                        |
|        `l`, `r`, `m`         |    left, right, middle    |                 常用于二分中                 |
|            `lch`             |        left child         |                                        |
|            `len`             |          length           |                                        |
|          `ll`, `LL`          |   `long long` (in C++)    |                                        |
|          `mi`, `mx`          |         min, max          |             （我个人不喜欢 `mi`）              |
|            `mid`             |          middle           |                                        |
|         `mod`, `MOD`         |          modulo           |         $10^9 + 7,\;998244353$         |
|            `mul`             |         multiply          |                                        |
|            `num`             |          number           |                                        |
|            `nxt`             |           next            |                                        |
|          `pi`, `PI`          |    $\pi = 3.14159...$     |          `cmath` 中提供了 `M_PI`           |
|            `pos`             |         position          |                                        |
|            `pre`             |          prefix           |                   前缀                   |
|            `pre`             |         previous          |                  上一个                   |
|            `pri`             |           prime           |                                        |
|            `ptr`             |          pointer          |                   指针                   |
|        `rand`, `rnd`         |          random           |                                        |
|            `rch`             |        right child        |                                        |
|            `ref`             |         reference         |                   引用                   |
|            `res`             |          result           |                                        |
|            `ret`             |          return           |                                        |
|            `rev`             |          reverse          |                                        |
|             `S`              |            set            |                 通常表示集合                 |
|           `s`, `t`           |   source, sink (target)   |           源点和汇点，在网络流和最短路中常见            |
|            `seg`             |          segment          |      You must know segment trees.      |
|            `seq`             |         sequence          |                                        |
|            `sqr`             |          square           |                 $x^2$                  |
|            `sqrt`            |        square root        |               $\sqrt x$                |
|            `stk`             |           stack           |                                        |
|            `str`             |          string           |                                        |
|            `suf`             |          suffix           |                   后缀                   |
|            `tmp`             |         temporary         |                  临时的                   |
|            `tot`             |           total           |            似乎 Pascal 选手喜欢用？            |
|        `u`, `v`, `w`         |    vertexes and weight    |                图论题中天天有                 |
|            `upd`             |          update           |                                        |
| `uX` `(X = 16, 32, 64, 128)` |     unsigned integer      |                 无符号整型                  |
|            `val`             |           value           |                                        |

当然，每个人都会有自己的喜好，你可以参照上面来简化你的命名规范。

(new part)