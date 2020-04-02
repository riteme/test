# 2020.1.10 训练报告

### A. Abnormal Words

**题意**　给定字符串，要你进行加密或者解密。

**题解**　模拟。



### B. Balanced Fighters

**题意**　给定 $n$ 个人，每个人有 HP、AT、DF 三个参数。两个人打架时会根据 AT、DF 得出每个人每轮的收到的伤害值。求所有的三元组 $A$、$B$、$C$ 满足 $A$ 能打赢 $B$，$B$ 能打赢 $C$，$C$ 能打赢 $A$。

**题解**　枚举三个人，然后看这三个人构成的竞赛图是否是一个环，即每个人的出度等于入度，且均为 $1$。



### C. Unjob Search

**题意**　已知树有 $n$ 个节点。可以使用至多 $n$ 次询问，每次询问给出三个点 $a$ 、$b$、$c$，交互器会返回 $c$ 是否在 $a$ 到 $b$ 的路径上。要求最后找出树上的一个叶子节点。

**题解**　以 $1$ 号点为根，初始时认为 $x = 2$ 号点为叶子，之后枚举$v$ 为 $3$ 到 $n$ 的所有点，如果 $x$ 在 $1$ 到 $v$ 的路径上，则 $v$ 在以 $x$ 为根的子树中，因此将 $x$ 设为 $v$ 即可。$n - 2$ 次询问后得到的 $x$ 就是树叶。



### E. Exciting Acts

**题意**　将一个长度为 $n$ 的序列分为 $K$ 段，每一段的权值为段内的最大值，问 $K$ 段的最大权值总和为多少。

**题解**　直接 DP 即可。



### G. Infinity Plus One

**题意**　一个程序中有三种操作：

* `+`：加 $1$。
* `[P]`：将程序 $P$ 执行 $ω$ 遍。
* `PQ`：先执行程序 $P$，再执行程序 $Q$。

现在给定 $n$ 个程序，要求按照每个程序最终给出的序数进行排序。

**题解**　每个程序 $P$ 可以对应一个序数 $(P)$，于是 `+` 就是 $1$，`[P]` 代表 $(P) \cdot ω$，而 `PQ` 表示 $(P) + (Q)$，之后使用序数的运算即可。



### H. Ancient Wisdom

**题意**　给定 $C$，求最小的正整数 $D$，满足存在 $CD^3$ 是一个平方数。$C < 2^{63}$。

**题解**　首先答案就是 $C$ 的质因数分解中所有次数为奇数的素因子的乘积。由于次数大于 $2$ 的素因子都小于 $10^7$，因此可以先暴力枚举将它们筛掉。之后剩下一个素因子，使得 $C$ 既可能是 $p$ 也可能是 $p^2$ 的形式，于是对 $C$ 开根判断一下即可。