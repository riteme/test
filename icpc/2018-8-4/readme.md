#### B. [Endless Pallet](https://www.nowcoder.com/acm/contest/144/B)

**题意**　给定一棵 $n$ 个节点的树，初始时每个节点为白色。每轮从树上所有的路径中随机选择一条，将路径上的节点全部染黑。问期望多少轮之后所有节点均被染成黑色。$n \leqslant 50$。

**题解**　令 $x_k$ 表示节点 $k$ 被染黑的时间，答案即为 $\mathbf{E}[\max\{x_k\}]$。同时注意到：

$$
\mathbf{E}[\max\{x_k\}] = \sum_{j = 0}^\infty \mathbf{P}[\max\{x_k\} \geqslant j]
$$

虽然 $\mathbf{P}[\max\{x_k\} \geqslant j]$ 不好求，但是 $\mathbf{P}[\min\{x_k\} \geqslant j]$ 很好求：只要前 $j$ 轮均不被染黑即可（这里当然 $j > 0$ 时不可能）。使用 *min-max* 反演来转化：

$$
\begin{aligned}
\mathbf{E}[\max\{x_k\}] &= \mathbf{E}\left[\sum_{S \subseteq\{1,...,n\}} (-1)^{|S| + 1} \min\{x_k:k\in S\} \right] \\
&= \sum_{S \subseteq\{1,...,n\}} (-1)^{|S| + 1} \mathbf{E}[\min\{x_k:k\in S\}] \\
&= \sum_{S \subseteq\{1,...,n\}} (-1)^{|S| + 1} \sum_{j = 0}^\infty \mathbf{P}[\min\{x_k:k\in S\} \geqslant j] 
\end{aligned}
$$

记 $A$ 为树上路径总数，$c(S)$ 为不经过 $S$ 内的点的路径总数，则 $\mathbf{P}[\min\{x_k:k\in S\} \geqslant j] = (c(S) / A)^j$。所以答案为：

$$
\sum_{S \subseteq \{1,...,n\}} (-1)^{|S| + 1} \cdot {1 \over 1 - c(S)/A}
$$

直接计算的时间复杂度为 $\Theta(2^n n^2)$。实际上对于每个集合 $S$，我们只关心 $|S|$ 的奇偶性和 $c(S)$ 的具体值，这一共只有 $\Theta(n^2)$ 种不同的项。所以考虑使用树型 DP 来计算。

设 $f(i,\,j,\,k,\,0/1)$ 表示：当前处理到节点 $i$，给出了 $|S|$ 的奇偶性（$0$ 代表偶数，$1$ 代表奇数），满足与 $i$ 相连的未在 $S$ 中的点构成的连通块大小（即 $i$ 附近有多少个点没选），并且 $c(S) = k$ 的集合 $S$ 总数。转移的时候考虑节点 $i$ 选还是不选，然后对 $j$ 、$k$ 两维做背包 DP 即可。

时间复杂度？我只会分析出 $O(n^6)$ 的上界，实际跑的挺快的……

#### I. [Team Rocket](https://www.nowcoder.com/acm/contest/144/I)

**题意**　初始给定 $n$ 个区间，之后进行 $q$ 次在线的操作。每次操作给出一个横坐标 $x$，要求将所有包含 $x$ 的区间全部删除，并输出被删除的区间个数。$n,\,q \leqslant 2 \times 10^5$。

**题解**　使用线段树维护所有区间左端点。在线段树上每个节点处开一个 `vector` 按照区间的右端点降序排序。这样每次操作就可以在线段树上查找所有满足要求的区间。由于每个区间只会被删除一次，所以时空复杂度为 $O((n + q) \log n)$。