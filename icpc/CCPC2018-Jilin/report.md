<br /><center class="subtitle">Fudan ACM-ICPC 2018</center>

# CCPC 2018 吉林赛区比赛报告

<br />
<center>$1/3$ 西瓜王薛振梁</center>
<center>2018 年 9 月 26 日</center>

<br />

### 比赛过程（个人视角）

比赛开始前 5min 就发了题。还是按照往常的模式，我顺序看题，ws 倒序，gmr 随机开。看到 A 题就是一个下取整分段求和就准备上，很快就过了。然后去看 B，发现无法理解样例。在 gmr 的猜测下总算解释通了样例，上机写后就过了。然后看 E 题，一开始没有思路，后来等 ws 来看后突然想到直接解方程，于是开始暴力计算。第一次少写了一个平方导致最后公式有误，没过样例。后面重算了一遍就 OK 了。再之后就进入了瓶颈期，看其它题发觉只有 G 和 J 可做。G 是构造题不太擅长，于是和 gmr 讨论 J。gmr 大胆猜想使得 J 进展很快，但没有得到做法。最后虽然想法已经相当接近，因时间不足放弃。

### 总结

这次比赛前期非常顺利，主要是从中期~~吃了中饭之后~~（此时已经过了 6 题）开始遇到困难。可能饱腹对思考有一些影响，导致 J 题错失出题机会。此外对题面很长的题缺乏有效的判断，如这次的 G 实际上是一个大模拟题，应当在中期就开始着手准备。

***

### 解题报告

#### A. The Fool

**题意**　求 $\sum_{k = 1}^n \lfloor n / k \rfloor$ 的奇偶性。$n \leqslant 10^9​$。

**题解**　直接分段计算求出来即可。

<hr />

#### B. The World

**题意**　给定一个地区的地方时，求此时另一个地区的地方时。

**题解**　直接模拟。

<hr />

#### E. The Tower

**题意**　给定一个圆锥，底面圆心位于原点，半径为 $r$，底面与 $xOy$ 平面平行。圆锥高度为 $h$。给出一颗子弹的初始位置 $(x_0,\ y_0,\ z_0)$ 与速度矢量 $v = (v_x,\ v_y,\ v_z)$，求在什么时候子弹击中圆锥。

**题解**　设时间为 $t$，此时子弹位于 $(x,\ y,\ z) = (x_0 + v_xt,\ y_0 + v_yt,\ z_0 + v_zt)$。则子弹在圆锥内部时满足：
$$
\begin{aligned}
t &\geqslant 0 \\
0 &\leqslant z \leqslant h \\
x^2 + y^2 &\leqslant \left(1 - \frac{z}h\right)^2r^2
\end{aligned}
$$
最后一个不等式是二次的，故解出其零点然后分类讨论即可。