<br /><center class="subtitle">Fudan ICPC Summer Training Camp 2019</center>

# 航电多校第三场训练报告

<br />
<center>刘明君、孙亮亮、薛振梁</center>
<center>2019 年 7 月 29 日</center>
<br />

### 概况

比赛中通过 5 题，赛后补 5 题，总共通过 10 题。

### 比赛过程

{: .replay}
```
|0        |30       |60       |90       |120      |150      |180      |210      |240      |270      (min)
......?x--G...............B......x.?...............................x.x?.....I......D...............j lmj
.....................................................?!!....!.....?...?.............x..............k sll
......................................F............................................................. xzl
-: Presentation Error
x: Wrong Answer
?: Time Limit Exceeded / Memory Limit Exceeded
!: Runtime Error
大写字母：Accepted
小写字母：未通过
```

### 总结

**刘明君：**我开场看 G，开始想用优先队列维护，写完发现复杂度不对，之后改成线段树，又 PE 了。浪费了一些时间，开始应该直接上线段树，就不会出问题。之后 I 是原题，敲上去之后超时，改了很长时间才过去。比赛中很长一段时间是过了 2 个题，手里有 5 个题，要加强中期题的写代码速度。

**孙亮亮：**代码能力有待加强，最近代码总是有细节错误，准备去刷一刷杀蚂蚁恢复一下代码能力。

**薛振梁：**这次比赛基本没有动手，只写了一道模板题。主要原因是大多数题目不能完整地想出解法，只有一个大概的感觉。今后做题要加强构思代码和验证算法的能力。

***

### 解题报告

#### A. Azshara's Deep Sea

**情况**　补题通过

**题意**　给 $n$ 个点，要求点的凸包，凸包上面可以站人，每次站两个人，在他们之间连线段，要求线段不能有交叉（除了端点），并且每条线段与输入的圆不相交，问最多连多少条线段。

**题解**　先求凸包，然后暴力判断每一对点可不可以连线段。因为要求线段不相交，可以区间 DP，算出答案。

<hr />
#### B. Blow up the City

**情况**　通过

**题意**　给一个 DAG，没有出度的点是关键点，每次输入两个点，问有多少个点，如果被删除，可以使得至少一个输入的点不能到任何关键点。

**题解**　支配树模板题。

<hr />
#### C. Yukikaze and Demons

**情况**　补题通过

**题意**　给定一棵 $n$ 个点的树，树上每个节点有一个 $0$ 至 $9$ 中的数字，问有多少条路径满足路径上的数字依次连接起来的大整数是给定常数 $K$ 的倍数。$n \leqslant 50000$，$K \leqslant 10^5$。

**题解**　考虑点分治中经过分治中心的一条路径，被分治中心分为 $A$ 和 $B$ 两部分，其中 $A$ 是大整数的前半部分，$B$ 是后半部分。设 $B$ 部分的长度为 $L(B)$，则该路径合法当且仅当 $A \cdot 10^{L(B)} + B \equiv 0 \pmod K$。若 $K$ 与 $10$ 互质，则求出 $10$ 的逆元后就可以快速统计出。否则将 $K$ 分解为 $2^p5^qm$ 的形式，其中 $m$ 与 $10$ 互质，于是根据中国剩余定理，只要前式分别模 $2^p$、$5^q$ 和 $m$ 时均等于 $0$ 即可。由于 $p,\ q \leqslant \log K$，所以当 $L(B)$ 较长时仅有模 $m$ 可能不为 $0$。因此对于小长度的 $B$ 枚举，大长度的 $B$ 则仅考虑模数 $m$。时间复杂度为 $\mathrm O(n \log n \log K)$。

<hr />
#### D. Distribution of Books

**情况**　通过

**题意**　给一个数列， 要求划分为 $k$ 个区间，求区间和的最大值最小是多少。并且可以把一个后缀丢掉不要。

**题解**　考虑二分答案，$\mathrm{dp}[i]$ 表示如果只考虑前 $i$ 个数，最多能划分出多少合法的段落，$\mathrm{dp}[i]=\max\{\mathrm{dp}[j]\} + 1$，$\mathrm{sum}(i)-\mathrm{sum}(j)\leqslant \mathrm{ans}$，可以用平衡树以 $-\mathrm{sum}(j)$ 为关键字排序，每次查询 $\leqslant \mathrm{ans} - \mathrm{sum}(i)$ 的数中 DP 值最大的。

<hr />
#### F. Fansblog

**情况**　通过

**题意**　求比质数 $P$ 小的最大的质数 $Q$ 的阶乘模 $P$ 的值。$P \leqslant 10^{14}$。

**题解**　首先直接枚举并用 Miller-Rabin 方法判断质数。考虑 Wilson 定理 $(P - 1)! \equiv -1 \pmod P$，因此暴力乘上逆元即可。

<hr />
#### G. Find the Answer

**情况**　通过（-4）

**题意**　给一个序列，对每个 $a_i$ 询问，在 $a_1...a_{i-1}$ 中，最少能挑出多少个数字，置为 $0$，能使得 $\sum_{j = 1}^i a_j \leqslant m$。

**题解**　用权值线段树维护出前缀的和，在线段树上边二分判断最少需要删除多少个数。

<hr />
#### H. Game

**情况**　补题通过

**题意**　Alice 和 Bob 玩取石子游戏，有 $n$ 堆石子，每次询问 $[L,\ R]$ 区间中，有多少子区间满足先手必胜，或者交换相邻的两堆石子。

**题解**　对石子做前缀和，相当于询问 $[L-1,\ R]$ 之间有多少对数字相同，修改是单点修改。可以用带修改的莫队快速维护。

<hr />
#### I. K Subsequence

**情况**　通过（-5）

**题意**　给一个序列，现在要求选出 $k$ 个不相交的非降子序列，要求使得 $k$ 个子序列的和最大，求最大值。

**题解**　考虑费用流，每个点拆为入点和出点，边权为 $1$，费用为 $a_i$，另一条边权无穷，费用为 $0$，每个点可以向后边的不小于他的点连边，跑费用流。$\mathrm O(n)$ 个点，$\mathrm O(n^2)$ 条边，一种可行的优化是用主席树优化建图，可以做到 $\mathrm O(n\log n)$ 个点，$\mathrm O(n\log n)$ 条边。

<hr />
#### J. Sindar's Art Exhibition

**情况**　补题通过

**题意**　在一棵树上，主人公沿一条树链走，开始有 $x$ 个作品，没经过一个点，先获得当前手中作品数 $×$ 该点权值 $f_i$ 的收益，之后 $x ← x - y_i$。每次询问一条链的收益和，或者修改单点的 $f$。

**题解**　考虑一次的收益是 $x\sum f_i - \sum y_i\cdot\mathrm{suffix}(f_i)$ 其中 $\mathrm{suffix}(f_i)$ 是 $y_i$ 当前点之后的所有 $f_i$ 之和。与 $x$ 相关的系数很好求，后面的截距之和路径有关，考虑如果是序列上的问题可以线段树维护区间的截距，把两个区间截距合并就是 $b_1+b_2+\mathrm{sum}(y_1)\cdot \mathrm{sum}(f_2)$，放到树上边就用树链剖分维护链上的截距，注意要维护正反两种走法。

<hr />
#### K. Squrirrel

**情况**　补题通过

**题意**　给一棵树，找到一个点使其到离他最远的点的距离最小，可以修改一条边的权值为 $0$。

**题解**　$f[i][0/1]$ 表示子树 $i$ 内不修改/修改边权，$i$ 到子树内的点的最小最远距离。

$g[i][0/1]$ 表示除子树 $i$ 外的点不修改/修改边权，$i$ 到其最小最远距离。

$f[i][0/1]$ 和 $g[i][0]$ 都很好处理，$g[i][1]$ 有三种情况，修改的边在 $i$ 的子树内和恰好为 $i-\mathrm{fa}[i]$ 这条边的也很好处理，至于修改的是 $\mathrm{fa}[i]$ 其他子树内的可以考虑记录最大和次大的 $f[j][0]+c[j]$ 来转移，$j$ 是 $\mathrm{fa}[i]$ 的儿子。