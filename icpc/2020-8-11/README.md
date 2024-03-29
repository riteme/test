 

06 Flower

题意：给定一棵树，树上有些花 $(u_i,r_i,w_i)$，$u_i$ 是花的中心，$r_i$ 是花的半径，$w_i$ 是价值。要求选出一些花，满足它们之间两两不相交，并且花的权值综合最大。

题解：$\mathrm{O}(n^2)$ DP 非常简单，只要记录一下子树内最顶上的花是谁就可了。

之后考虑启发式合并。相当于枚举较小的一边的子树最顶上的花，一方面会从大子树中一段区间转移过来，这个只用在平衡树上记录最大值。另一方面是这朵花会对大子树一段区间的 DP 值有贡献。这里需要注意一下，因为不能对标记取 max，所以必须要把所有小子树中的花的贡献一起做一个扫描线，最后再一起做修改。

