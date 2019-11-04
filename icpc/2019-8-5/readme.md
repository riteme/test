<br /><center class="subtitle">Fudan ICPC Summer Training Camp 2019</center>

# 杭电第五场训练报告

<br />
<center>[Fudan U2] 刘明君、孙亮亮、薛振梁</center>
<center>2019 年 8 月 5 日</center>
<br />

### 概况

比赛中通过 4 题，赛后补 4 题，总共通过 8 题。

### 比赛过程

<pre class="replay">
|0........|30.......|60.......|90.......|120......|150......|180......|210......|240......|270...... (min)
            G                              D                         h                !!      x    b [lmj]
                                    x   xxxD             E                                         j [sll]
             F     xx                   +     xe                    xh                             j [xzl]
*^^^^^^^^^*^^^^^^^^^*^^^^^^^^^*^^^^^^^^^*^^^^^^^^^*^^^^^^^^^*^^^^^^^^^*^^^^^^^^^*^^^^^^^^^*^^^^^^^^^
 x   Wrong Answer / Presentation Error              !   Runtime Error
 +   Time Limit Exceeded                            =   Memory Limit Exceeded
A-N  Accepted                                      a-n  可做但未通过 / 弃题
</pre>

### 总结

**刘明君：**比赛时候 4 道签到题通过的太慢了，最后的时候，H 想出了正确做法，但是几何题的细节太多了，xzl 没有调出来。B 想了一个看着卡不掉的做法最后也没有写完，暴力不能拖到太晚写，应该前期敲一个出来方便调试和卡常，说不定就过了。

**孙亮亮：**代码总是没办法一遍过，总有些细节问题需要 gdb 或肉眼查错，需要改进。

**薛振梁：**这一场题风比较诡异。我主要是 E 题没有想清楚就开始写，最后还是给 sll 写才过掉，浪费了很多时间。

***

### 解题报告

#### A. Fraction

**情况**　补题通过

**题意**　求一组 ${a\over b } \equiv x \pmod p$，输入 $x,\ p$ 求最小可行的 $b$。

**题解**　令 $a=bx-py$，$0<a<b$，则 ${x-1\over p}<{y\over b}<{x\over p}$，求两个分数中间的最佳分数，用连分数展开可以做。

<hr />
#### B. Three Arrays

**情况**　补题通过

**题意**　给两个数组 $a_i,\ b_i$，现在可以对两个数组各自任意重排序，要求 $c_i=a_i \oplus b_i$ 的字典序最小。

**题解**　(lmj) 可以贪心每次选择一个最小的异或值出来，如果有多个，可以任意挑一个出来，因为不管怎么选，一定可以把所有异或出这个数的 pair 全都选出来，不会出现因为顺序问题导致选少了的情况。

把两个数组放到 trie 上，然后按照深度倒序 BFS 整棵树，如果在叶子上面既有 $a_i$ 也有 $b_j$，那么可以直接选了，如果非叶子上面都有，那么就暴力把左右两颗子树合并，并且在这下面的答案都加上这个点表示的 $2$ 的幂次，向下递归做这个过程，直到里面只有 $a$ 或只有 $b$。复杂度可能是 $\mathrm O(n\log^2n)$ 的。

(xzl) 考虑最终每对 pair 的匹配过程，其匹配点是从 trie 的根一直走到某一个叶子处。而暴力的过程中如果没有匹配上就不会往下走，所以总复杂度是 $\mathrm O(n \log W)$ 的。

<hr />
#### D. Equation

**情况**　通过

**题意**　给出两个序列 $a$、$b$，求 $\sum |a_ix+b_i| = C$ 的 $x$。

**题解**　$x=-\infin$ 时所有 $a_i x+b_i$ 一定取相反数，$x=\infin$ 时所有 $a_ix+b_i$ 取本身的值，对于 $a_ix+b_i$，当 $x=-b_i/a_i$ 时将会变号，因此当 $x$ 在某段区间时各项正负一定，因而求出 $x$ 看是否在这段区间即可。

<hr />
#### E. Permutation 1

**情况**　通过

**题意**　求出一个 $1$-$n$ 的排列使其差分序列字典序第 $K$ 小。

**题解**　未放入的数字个数 $>10$ 时只会有一种选择，$\leqslant 10$ 时枚举剩余的所有排列即可。赛场上写的方法是维护一个可行解集合，每个可行解被表示为 $\{p,\ S\}$，其中 $p$ 代表第 $i-1$ 个数是什么，$S$ 代表哪些数已经使用，枚举第 $i$ 位的差找到第 $K$ 大所对应的差，从而可以求出差分序列，用最终的唯一可行解来倒推出原序列。

<hr />
#### F. String Matching

**情况**　通过

**题意**　给定一个字符串，问字符串每个后缀对原串的 LCP 之和是多少。

**题解**　ExKMP 模板题。

<hr />
#### G. Permutation 2

**情况**　通过

**题意**　问在 $1$-$n$ 的全排列中，有多少个满足 $a_1=x,\ a_n=y,\ |a_i-a_{i+1}|\leqslant 2$。

**题解**　可以发现如果 $x$ 不是 $1$，那么开始一定是先要 $x-2,\ x-4,\ ...,\ 2,\ 1,\ 3,\ 5,\ ...,\ x-3,\ x-1,\ x+1$ 同理，结尾的时候 $y$ 如果不是 $n$ 也有类似的情况。所以只需考虑 $1,\ ...,\ n$ 有多少种情况。考虑下一个数字是 $x+1$ 还是 $x+2$，如果是 $x+2$，之后就是 $x,\ x+2,\ x+1,\ x+3,\ ...$ 所以是一个线性递推式，算出每一项就可以了。

<hr />
#### H. Line Symmetric

**情况**　补题通过

**题意**　给定一个 $n$ 个顶点的简单多边形，现在可以最多平移一个点的位置，要求平移后依然为简单多边形，并且是一个轴对称多边形。问是否有解。$n \leqslant 1000$。这里的轴对称是要求顶点位置要一一对应。

**题解**　首先对于 $n \leqslant 4$ 的情况是一定有解。对于 $n > 4$ 的情况，对于一条可能的对称轴，最多只有一对点的位置出错。所以我们枚举顶点和边，那么对称轴一定是最开始两对点的中垂线，使用线性的算法判定对称轴是否合法即可。时间复杂度 $\mathrm O(n^2)$。注意判断时要小心对称轴两边的角都与对称轴相交的情况，这种情况下是不能平移点的，因为图形会变成非简单多边形。

<hr />
#### I. Discrete Logarithm Problem

**情况**　补题通过

**题意**　求 $a^x\equiv b \pmod p$，但是 $p\leqslant 10^{18}$，并且 $p$ 的质因子只有 $2,\ 3$。

**题解**　Pohlig-Hellman 算法模板题。