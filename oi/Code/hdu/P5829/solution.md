首先将$a$数组降序排好，下标从$0$开始。
考虑每一个数对答案的贡献，将所有集合排下来，$k$的答案就是一个二维前缀和。
令答案为$g(k)$，那么可以考虑每一行的新贡献来得到递推式：
$$
\begin{aligned}
g(-1) & = 0 \\
g(k) & = g(k - 1) + \sum_{i = k}^{n - 1} a_i \binom{i}{k} 2^{n - i - 1}
\end{aligned}
$$

令$f(k)$为后面那个和式，现在的目标就是求出$f(0)$到$f(n - 1)$。
尝试将$f(k)$化为两个函数卷积的形式，首先一步就是要将下标从$0$开始：
$$
\begin{aligned}
f(k) & = \sum_{i = k}^{n - 1} a_i \binom{i}{k} 2^{n - i - 1} \\
& = \sum_{i = 0}^{n - k - 1} a_{i + k} {(i + k)! \over k!i!} 2^{n - i - k - 1}
\end{aligned}
$$

剩下的，就是尽可能使和式内部简单，并尝试靠近一般卷积的形式：
$$
\begin{aligned}
f(k) & = \sum_{i = 0}^{n - k - 1} a_{i + k} {(i + k)! \over k!i!} 2^{n - i - k - 1} \\
& = \frac1{k!2^{k + 1}} \sum_{i = 0}^{n - k - 1} a_{i + k} (i + k)! \frac{2^{n - i}}{i!}
\end{aligned}
$$

到这一步时，可以考虑将$i + k$相关的放在一起，剩下的放在一起。于是令：
$$
\begin{aligned}
A(k) & = k!a_k \\
B(k) & = {2^{n - k} \over k!}
\end{aligned}
$$

于是$f(k)$表达式可以简写为：
$$
f(k) = \sum_{i = 0}^{n - k - 1} A(i + k)B(i)
$$

Fuck!现在还不是卷积的形式，因为$i + k + i \neq n - k - 1$。但是我们可以对$A$调动一下：
$$
C(k) = A(n - k - 1)
$$

那么：
$$
f(k) = \sum_{i = 0}^{n - k - 1} C(n - k - i - 1)B(i)
$$

这样就可以使用NTT来加速运算了。
