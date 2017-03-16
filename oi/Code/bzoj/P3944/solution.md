考虑下面的和式：
$$
\begin{aligned}
\sum_{i = 1}^n \sum_{d \mid i} f(i) & = \sum_{d = 1}^n f(d) \left\lfloor {n \over d}  \right\rfloor \\
& = \sum_{d = 1}^n \sum_{i = 1}^{\lfloor n / d \rfloor} f(i)
\end{aligned}
$$

为什么上式会等于下式？首先在上面的式子中$f(i)$会贡献$\lfloor n / i \rfloor$次。
而在下面的式子中，$f(i)$会贡献当且仅当$id \leqslant n$，这样的$d$共有$\lfloor n / i \rfloor$个，因此贡献了同样的次数。所以这两个式子相等。
注意到第二个式子很妙，因为后面是同样的问题：计算前缀和。同时注意到，原先计算的前缀和等于：
$$
\begin{aligned}
\sum_{d = 1}^n \sum_{i = 1}^{\lfloor n / d \rfloor} f(i) - \sum_{d = 2}^n \sum_{i = 1}^{\lfloor n / d \rfloor} f(i) = \sum_{i = 1}^n \sum_{d \mid i} f(i) - \sum_{d = 2}^n \sum_{i = 1}^{\lfloor n / d \rfloor} f(i)
\end{aligned}
$$

一些数论中的积性函数有一些很好的公式，如：
$$
\begin{aligned}
\sum_{d \mid n} \varphi(d) & = n \\
\sum_{d \mid n} \mu(d) & = [n = 1]
\end{aligned}
$$

所以它们的左半部分可以快速计算($\Theta(1)$)。而右半部分则采用记忆化搜索来计算。

时间复杂度分析？
考虑递归的过程，由于下取整的取值是$O(\sqrt{n})$级别的，所以，如果接下来的前缀和都已经计算过，那么单次复杂度为$O(\sqrt{n})$。
由于递归过去可能并没有计算过，那么复杂度应为：
$$
\sum_{k = 1}^{\lfloor \sqrt{n} \rfloor} \sqrt{k} + \sum_{k = 1}^{\lfloor \sqrt{n} \rfloor} \sqrt{n \over k}
$$

显然右边的代价更高。用积分可以估计一下：
$$
\sum_{k = 1}^{\lfloor \sqrt{n} \rfloor} \sqrt{n \over k} \leqslant \int_0^{\lfloor \sqrt{n} \rfloor} \sqrt{n \over x} \;\mathrm{d}x = O(n^{3/4})
$$

如果预处理前$S$个前缀和的答案，那么复杂度大约为：
$$
\sum_{k = 1}^{\min\{\lfloor \sqrt{n} \rfloor, \lfloor n / S \rfloor\}} \sqrt{n \over x}
$$

当$S \lt \sqrt{n}$时，时间复杂度的分析不变。否则时间复杂度上界变为：
$$
O\left(S + {n \over \sqrt{S}}\right)
$$

当$S = n / \sqrt{S}$时取得最大值，此时$S = n^{2/3}$，时间复杂度也为$O(n^{2/3})。$
