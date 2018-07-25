<center><font style="font-size: 20px">NOIP 模拟赛 Day 1</font></center>
<center>by riteme</center>
<br/>
### <center>赛跑</center>
#### Tags
图论 / 深度优先搜索、最优性剪枝。

#### 题解
首先可以使用最简单的暴力搜索，就可拿到 $50$ 分，是不是非常良心？

之后我们注意到 $m \leqslant n + 20$ 这个奇怪的条件，我们可以脑补一下这张图是是什么样子，显然是存在很多度数为 $2$ 的点，意思是图中会有很多长链。而这些长链从一个点进入，就必须从链的另外一端出来，中间是没有任何选择的。所以我们可以将这样的长链都缩成一条边，这样图的规模就会大大减小，可以通过所有的测试点。

*****

### <center>螺旋之美</center>
#### Tags
结论 / 逆序对。

#### 题解
题面非常良心，$n = 4$ 的情况已经只差一种了，再之后就会不断循环了。实际上，这个过程生成了所有的长度为 $n$ 的排列。

我们可以使用一种更程序化的方法来描述这个过程，首先从排列 $123...n$ 开始，每个数字上方都写一个方向，初始时都向左。下面将以 $n = 3$ 为例：

$$ \stackrel{\small\leftharpoonup} 1\stackrel{\small\leftharpoonup}2\stackrel{\small\leftharpoonup}3 $$

如果一个数字的箭头所指的方向的下一位有一个比它小的数，那么这个数字就是可移动的。例如，上面的 $2$ 和 $3$ 就都是可移动的。然后，我们每次从所有可移动的数字中选出最大的那一个，将它与它的箭头所指的方向的下一个交换位置：

$$ \begin{matrix} \stackrel{\small\leftharpoonup}1\stackrel{\small\leftharpoonup}3\stackrel{\small\leftharpoonup}2 \\ \stackrel{\small\leftharpoonup}3\stackrel{\small\leftharpoonup}1\stackrel{\small\leftharpoonup}2 \end{matrix} $$

注意到现在我们只能移动 $2$ 了。此时我们再添加一条规则，就是如果当前移动的是 $x$，那么就将所有比 $x$ 大的数字的箭头方向调转：

$$ \stackrel{\small\rightharpoonup}3\stackrel{\small\leftharpoonup}2\stackrel{\small\leftharpoonup}1 $$

这样我们就可以继续：

$$ \begin{matrix} \stackrel{\small\leftharpoonup}2\stackrel{\small\rightharpoonup}3\stackrel{\small\leftharpoonup}1 \\ \stackrel{\small\leftharpoonup}2\stackrel{\small\leftharpoonup}1\stackrel{\small\rightharpoonup}3 \end{matrix} $$

注意到我们的算法会在 $21345...$ 这种排列时停止运行，而它的下一行就是 $12345...$，这样使得这个过程可以不断循环下去。

通过模拟这个过程，我们可以得到 $30$ 分。

现在需要优化这个过程，这必定不能从一开始就模拟，我们需要直接计算出每个数字上箭头的方向，从而能够知道交换哪两个地方的值。

注意到数字上的箭头会改变方向当且仅当有一个比它小的数字进行了移动。由于箭头只有两种方向，所以我们只用知道这个次数的奇偶性就可以了。观察可以发现，如果令 $c_x$ 表示位置在 $x$ 后面却比 $x$ 小的数字的个数，那么一个数字 $x$ 箭头变化次数的奇偶性和 $\sum_{k = 1}^{x - 1} c_k$ 是一样的。所以我们可以通过计算这个东西来得知每个数字上箭头的方向。

$c_1..c_n$ 的统计可以使用树状数组 / 线段树 / 平衡树来实现，时间复杂度为 $O(n \log n)$。

*****

### <center>储能树</center>
#### Tags
数据结构 / 树链剖分、线段树。

#### 题解
如果只要计算一次，考虑将无根树转为有根树，然后 DFS 一遍计算以每个节点为根的子树中的边权之和。根节点的这个值就是总边权之和。用对于每条边，用深度较大的节点来记录这条边上的信息 $a$ 和 $b$。$a$ 表示子树中的边权之和，$b$ 表示子树外的边权之和(当然要除去这条边)。然后在 $\Theta(n)$ 的时间内可以计算出答案。

接下来考虑维护答案。对于每条边的修改，自己的 $a$ 和 $b$ 不会有影响，对于从这条边到根节点的链上的每一条边的 $a$ 值都会增加，而对于其它的边的 $b$ 值都会增加。因此我们用 $\Delta a$ 和 $\Delta b$ 来记录每一条边的增量，这个值可以利用树链剖分 + 线段树来维护，链上的边直接增加，其它边先全局打上标记，然后对不需要的边打上减去的标记即可。

最后在线段树的根节点统计答案，利用求和的性质即可：

$$ \begin{aligned} \sum^n_{i=1} a'_i b'_i & = \sum^n_{i=1} (a_i + \Delta a)(b_i + \Delta b) \\ & = \sum^n_{i=1} a_ib_i + \Delta a\sum^n_{i=1}b_i + \Delta b\sum^n_{i=1} a_i + n\Delta a\Delta b \end{aligned} $$

从这也能看出维护 $\sum^n_{i=1} a_ib_i$、$\sum^n_{i=1}b_i$ 和 $\sum^n_{i=1} a_i$ 这三个和式和 $\Delta a$ 和 $\Delta b$ 这两个标记就可以完成维护。时间复杂度为 $O((n + q)\log^2n)$。当然你会 LCT 的话可以追求理论更优的 $O((n + q) \log n)$ 的时间复杂度。
