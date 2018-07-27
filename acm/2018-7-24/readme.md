<center class="subtitle">Fudan ACM-ICPC Summer Training Camp 2018</center>
# 第 1 场训练报告
<br />
<center>薛振梁</center>
<center>2018 年 7 月 24 日</center>
<br />

### 概况

比赛中通过 8 题，赛后补 3 题，总共通过 11 题。

### 比赛过程

开局：C（14min）、B（33min）、I（44min）、H（54min）、F（78min）、E（91min）。

之后到 188min 才过了 A，因为一开始数据结构学傻了，先写了个平衡树，提交后 T 掉了，然后又换成二分才过。直到比赛结束前都没想到滑动窗口。

198min 时交了一发 D，实际上是正解，但是因为没用 `long long` 而 WA 了，考后才发现。

最后 226min 过了 M，之后弃疗。

### 总结

这次训练总体情况还好，主要失误在 A 题上，因为写平衡树 T 了很多发并且浪费了很多时间。虽然最后还是 A 了，但不是最优解法。说明很多技巧性的东西已经忘得差不多了，是时候补一下了。

D 题是个经典错误：忘记开 `long long`。WA 了一发之后因为被题目中 $m$ 的范围迷惑了而没有自信再改下去了。提交前的测试也不够充分。以后还是要胆子大一些，不然被出题人耍了都不知道 TAT

***

### 解题报告

#### A. [Careful Thief](https://codeforces.com/gym/101810/problem/A)

**情况**　AC

**题意**　给出 $n$ 段互不相交的区间，以及每个区间内元素的值。找出长度至多为 $k$ 的区间，使得区间和最大。$n \leqslant 10^5$，区间端点范围 $[1,\,10^9]$。

**题解**　首先依据贪心的原理，不难发现答案区间的某个端点一定和给出的区间中某个端点重合。之后关键就在于区间互不相交，使用滑动窗口从左至右扫一遍即可。时间复杂度 $\Theta(n)$。

<hr />

#### B. [Friends and Cookies](https://codeforces.com/gym/101810/problem/B)

**情况**　AC

**题意**　有 $n$ 个糖果，发给 $m$ 个人，按照 $1,\,2,\,3,\,...,m,\,m-1,\,m - 2,\,...$ 的顺序来发，求最后每个人得到了多少糖果。$n \leqslant 10^{18}$，$m \leqslant 1000$。

**题解**　先用 $2m - 2$ 为循环节填充，剩余部分模拟。时间复杂度 $\Theta(m)$。

<hr />

#### C. [Flip the Bits](https://codeforces.com/gym/101810/problem/C)

**情况**　AC

**题意**　给出数 $x$，求出最少翻转多少二进制位才能变成 $x - 1$。$1 \leqslant x \leqslant 10^9$。

**题解**　答案为 `__builtin_popcount(x ^ (x - 1))`。时间复杂度 $\Theta(1)$ 或者 $O(\log n)$。

<hr />

#### D. [Magic Sticks](https://codeforces.com/gym/101810/problem/D)

**情况**　WA，已补

**题意**　给定 $n \times m$ 的网格图，选出最少的不相交的长度为 $1$ 的边，使得每个格子至少被覆盖一次。输出最少的数量。$n \leqslant 10^9$，$m \leqslant 1024$。

**题解**　对于每一竖排，隔一个放一个，相邻竖排之间要错开放。这样就是最佳方案。

对 $n \times m$ 和 $m \times n$ 都考虑一遍，取最小值即可。时间复杂度 $\Theta(1)$。

<hr />

#### E. [N-Dimensional Grid](https://codeforces.com/gym/101810/problem/E)

**情况**　AC

**题意**　给出一个 $n$ 维网格，第 $k$ 维的长度为 $a_k$，求出网格中相邻的格子对数。答案对质数 $M = 10^9  +7$ 取模。$n \leqslant 10^5$。

**题解**　所谓相邻就是两个坐标之间只有一维的坐标值差 $1$。

令 $P = \prod_{k = 1}^n a_k$，答案显然为 $\sum_{k = 1}^n (a_k - 1) \cdot P / a_k$。时间复杂度 $O(n \log M)$。

<hr />

#### F. [Minimum Sum of Array](https://codeforces.com/gym/101810/problem/F)

**情况**　AC

**题意**　给出长度为 $n$ 的序列 $A$，如果存在 $A_i \mid A_j$，就可以把 $A_j$ 变成 $A_i$。求出最后序列总和的最小值。$n \leqslant 10^5$，$A_i \leqslant 10^6$。

**题解**　显然一个数能改就改，并且最后应该是改成自己的最小因子。于是使用像普通筛法一样的算法来进行修改即可。时间复杂度 $O(A \ln A)$，$A = \max\{A_i\}$。

<hr />

#### G. [Power of String](https://codeforces.com/gym/101810/problem/G)

**情况**　已补

**题意**　给定长度为 $n$ 的只包含小写英文字母的字符串 $S$，定义 $P(S)$ 为：
$$
P(S) = \sum_{k = 1}^n N_k \cdot S_k
$$

其中 $N_k$ 是 $S_k$ 之后中字母和 $S_k$ 相同的个数，$S_k$ 表示字母的 ASCII 码。现在一共有 $K$ 次修改的机会（不一定要全部用完），每次可以将 $S$ 中的某个字母改为任意一个小写英文字母。求修改后 $P(S)$ 的最小值。$n \leqslant 10^5$，$K \leqslant 5000$。

**题解**　首先要注意到 $P(S)$ 的计算方法不止一种：用 $1..26$ 表示字母 `a`-`z`，记 $m = 26$，令 $C_k$ 表示字母 $k$ 在 $S$ 中的出现次数，和 $w_k$ 表示字母 $k$ 的 ASCII 码，那么：
$$
P(S) = \sum_{k = 1}^m {C_k \choose 2}\cdot w_k
$$
每次修改操作相当于是将某个 $C_i$ 减 $1$，将另外一个 $C_j$ 加 $1$。

注意到三个性质：

* 不会出现 $a \rightarrow b$，然后又 $b \rightarrow c$ 的情况，因为直接 $a \rightarrow c$ 就好了。
* 如果有 $a \rightarrow b​$ 和 $c \rightarrow d​$，那么这样修改后的 $P(S)​$ 不会超过 $a \rightarrow b​$、$c \rightarrow b​$ 和 $a \rightarrow d​$、$c \rightarrow d​$ 中的最大值。因为如果 $C_b​$ 加 $1​$ 得到收益更大，那么连续两次改成 $b​$ 得到的收益不会小于一次修改 $C_b​$、一次修改 $C_d​$ 的收益。修改 $C_d​$ 收益更大同理。
    * 综合上述两点，所有修改操作都会改成同一个字母。
* 类似第二点，如果修改 $C_a$ 损失较少，就会一直修改 $C_a$。
    * 所以每段修改都是会把某种字母全部改掉，除非受到了修改次数上界 $K$ 的限制。

因为只有最后一种被修改的字母不一定会全部改掉，其它的字母一改就是全改，所以先使用 $O(m^2)$ 的时间枚举修改操作的目标字母和最后一个被修改的字母，其余的字母按照 $C_k$ 为大小进行背包 DP：记录 $f[i][j]$ 表示前 $i$ 个字母中使用了大小为 $j$ 的背包所能得到的最大的 $P(S)$ 是多少。这个 DP 是 $O(mK)$ 的。最后利用这个 DP 数组来计算最后一个被修改的字母的贡献。时间复杂度 $O(n + m^3K)$，空间复杂度 $\Theta(m + K)$。

<hr />

#### H. [Making Friends](https://codeforces.com/gym/101810/problem/H)

**情况**　AC

**题意**　给出 $2n$ 个人，以及每个人的权值，并且 $2n$ 人配成 $n$ 对，求出每对中权值和的最大值。$n \leqslant 1000$。

**题解**　模拟即可。时间复杂度 $\Theta(n)$。

<br /><br />

#### I. [Split the Number](https://codeforces.com/gym/101810/problem/I)

**情况**　AC

**题意**　给出 $x$ 和 $n$，要求将 $x$ 分为 $n$ 个正整数，并且这 $n$ 个正整数的极差最小。$x \leqslant 10^9$，$n \leqslant 1000$。

**题解**　$x \bmod n$ 个数为 $\lfloor x / n \rfloor + 1$，其余均为 $\lfloor x / n \rfloor$。时间复杂度 $\Theta(n)$。

<hr />

#### J. [T-Shirts Dilemma](https://codeforces.com/gym/101810/problem/J)

**情况**　已补

**题意**　有一堆商品，价格分别为 $l,\,l + 1,\,l + 2,\,...,\,r$。可以购买其中价格连续的一些商品，最后支付的金额为所有购买的商品的价格按位或和（OR 和）。给出身上所带的钱数 $v$，问最多能买多少件商品。$l,\,r,\,v \leqslant 10^{18}$。

**题解**　类似数位 DP 的思路，按照 $v$ 的二进制从高位到低位逐位考虑。

总体原则：如果从某一为开始 OR 和比 $v$ 小，那么下面的所有商品均可选。

具体的算法流程：

* 如果 $v$ 的当前位为 $1$，那么所有这一位为 $0$ 的区间均可直接全选：对答案取最大值。然后继续考虑下一位。
* 如果 $v$ 的当前位为 $0$，那么所有这一位为 $1$ 的区间均不可选。考虑其余这一位为 $0$ 的区间：
    * 如果包含了完整的区间，则将范围缩小到该区间并考虑下一位。
    * 如果左右端点在同一个区间内，则继续考虑下一位。
    * 如果左右端点分属两个不同的区间，分别递归到这两个区间处理并取最大值。

使用 DFS 处理上述流程。类似于线段树中的理论，上述步骤中最后一项最多执行一次。所以时间复杂度为 $\Theta(\log v)$。

<hr />

#### <span style="color: red">K.</span> [*League of Demacia*](https://codeforces.com/gym/101810/problem/K)

**情况**　**未补**

**类别**　计算几何

<hr />

#### <span style="color: red">L.</span> [*Lazy Teacher*](https://codeforces.com/gym/101810/problem/L)

**情况**　**未写代码**

**题意**　给定 $n \times m$ 的网格，每个格子可以填入 $1..k$ 中的一个数，要求相邻的两个格子中不能填一样的数字，求总方案数。$n \leqslant 5$，$m \leqslant 10^4$，$k \leqslant 10^5$。

**题解**　$n$ 非常小，状压 DP 即可。过程类似于逐格转移的插头 DP（轮廓线 DP）。

<hr />

#### M. [Greedy Pirate](https://codeforces.com/gym/101810/problem/M)

**情况**　AC

**题意**　给出一棵 $n$ 个点的树，树上每条边有两个权值 $w_1$ 和 $w_2$，分别表示正着走和反着走的收益。有 $q$ 个询问，每次给出起点 $u$ 和终点 $v$，要求每条边至多经过两次，求出从 $u$ 走到 $v$ 的最大收益是多少。$n,\,q \leqslant 10^5$。

**题解**　类比欧拉路径，最后只有从 $v$ 到 $u$ 的简单路径无法走，因此答案就是所有的边权和减去从 $v$ 到 $u$ 的简单路径和。

使用 DFS 预处理和 LCA 算法即可。时间复杂度 $O(n + q \log n)$（树链剖分求 LCA）。
