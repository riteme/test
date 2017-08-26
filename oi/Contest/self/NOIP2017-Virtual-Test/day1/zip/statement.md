<br />
<br />
<br />
<center><font style="font-size: 35px">NOIP 模拟赛</font></center>
<br />
<center><font style="font-size: 40px">Day 1</font></center>
<br />
<br />
<br />
<br />
<br />
<br />
<table style="width: 100%">
<tr><td width="25%">题目名称</td><td width="25%">赛跑</td><td width="25%">螺旋之美</td><td>储能树</td></tr>
<tr><td>英文名称</td><td><code>run</code></td><td><code>spiral</code></td><td><code>tree</code></td></tr>
<tr><td>输入文件</td><td><code>run.in</code></td><td><code>spiral.in</code></td><td><code>tree.in</code></td></tr>
<tr><td>输出文件</td><td><code>run.out</code></td><td><code>spiral.out</code></td><td><code>tree.out</code></td></tr>
<tr><td>时间限制</td><td>$2\mathrm{s}$</td><td>$1\mathrm{s}$</td><td>$1\mathrm{s}$</td></tr>
<tr><td>空间限制</td><td>$512\mathrm{MB}$</td><td>$512\mathrm{MB}$</td><td>$512\mathrm{MB}$</td></tr>
<tr><td>测试点个数</td><td>$10$</td><td>$10$</td><td>$10$</td></tr>
<tr><td>单个测试点分值</td><td>$10$</td><td>$10$</td><td>$10$</td></tr>
<tr><td>是否有附加文件</td><td>是</td><td>是</td><td>是</td></tr>
<tr><td>题目类型</td><td>传统型</td><td>传统型</td><td>传统型</td></tr>
<tr><td colspan="4">提交文件需加后缀：</td></tr>
<tr><td>对于 C\+\+ 语言</td><td><code>run.cpp</code></td><td><code>spiral.cpp</code></td><td><code>tree.cpp</code></td></tr>
<tr><td>对于 C 语言</td><td><code>run.c</code></td><td><code>spiral.c</code></td><td><code>tree.c</code></td></tr>
<tr><td>对于 Pascal 语言</td><td><code>run.pas</code></td><td><code>spiral.pas</code></td><td><code>tree.pas</code></td></tr>
<tr><td colspan="4">编译选项：</td></tr>
<tr><td>对于 C\+\+ 语言</td><td><code>-O2 -std=c\+\+11 -lm</code></td><td><code>-O2 -std=c\+\+11 -lm</code></td><td><code>-O2 -std=c\+\+11 -lm</code></td></tr>
<tr><td>对于 C 语言</td><td><code>-O2 -lm</code></td><td><code>-O2 -lm</code></td><td><code>-O2 -lm</code></td></tr>
<tr><td>对于 Pascal 语言</td><td><code>-O2</code></td><td><code>-O2</code></td><td><code>-O2</code></td></tr>
</table>

*****

### <center>赛跑</center>

<br />

#### 题目描述
长者国马上要举行一次盛大的马拉松赛跑了！全国各地的记者在首都欢聚一堂，参加这一意义重大的比赛。有一位长者在首都画了一个圈，作为比赛的赛道。同时，为了增加趣味性，这条赛道还添加了一些“捷径”。当然，这些捷径并不意味着一定可以更快地到达终点。但是记者们的目标就是要充分利用赛道的特性来展现自己裤腰带的高度。

具体来讲，赛道上一共有 $n$ 个地点，编号为 $1..n$。某些地点之间可能存在相连的跑道。记者们将在 $1$ 号地点起跑，**经过每个地点一次**之后回到 $1$ 号地点。例如，在下面的赛道中：

<img width=180px src="https://git.oschina.net/riteme/blogimg/raw/master/other/vnoipday1-1.svg" />

路径 $1 - 2 - 3 - 4 - 1$ 是允许的，而 $1 - 2 - 4 - 1$ 和 $1 - 2 - 3 - 4 - 2 - 1$ 是不允许的。

作为来自全世界记者跑的最快的地区的你，早已经打听到赛道的具体情况。于是你想知道这一次赛跑你最少要花多少时间。

#### 输入格式
从文件 `run.in` 输入数据。

第一行输入两个正整数 $n$ 和 $m$，表示地点的数量和跑道的数量。

接下来 $m$ 行，每行三个正整数 $u$、$v$ 和 $t$，表示 $u$ 号地点和 $v$ 号地点之间的一条跑道，并且通过这条跑道你需要花费 $t$ 分钟。

我们认为**经过每个地点是不需要花费时间的**。

#### 输出格式
输出到文件 `run.out` 中。

输出一行一个整数，表示最少需要多少分钟，你才可以完成赛跑。

#### 样例 1
##### 输入
```
4 5
1 2 1
2 3 1
3 4 1
4 1 1
2 4 1
```

##### 输出
```
4
```

#### 样例 2
##### 输入
参见下发文件 `run2.in`。

##### 输出
参见下发文件  `run2.ans`。

*****

#### 限制与约定
对于 $100\%$ 的数据，满足 $n \leqslant 10^5$，$n \leqslant m \leqslant n + 20$，$1 \leqslant u,\;v \leqslant n$，$1 \leqslant t \leqslant 100$。并且数据保证你可以找到一组合法的方案。

对于每个测试点限制如下：

<table class="detail-table">
<thead>
<tr><th width=50%>测试点编号</th><th>$n$ 的规模</th></tr>
</thead>
<tbody>
<tr><td>$1$</td><td rowspan="3">$\leqslant 10$</td></tr>
<tr><td>$2$</td></tr>
<tr><td>$3$</td></tr>
<tr><td>$4$</td><td rowspan="2">$\leqslant 20$</td></tr>
<tr><td>$5$</td></tr>
<tr><td>$6$</td><td>$\leqslant 1000$</td></tr>
<tr><td>$7$</td><td>$\leqslant 10000$</td></tr>
<tr><td>$8$</td><td rowspan="3">$\leqslant 100000$</td></tr>
<tr><td>$9$</td></tr>
<tr><td>$10$</td></tr>
</tbody>
</table>

*****

### <center>螺旋之美</center>

<br />

#### 题目描述
自然界中，有规律的事物总是美妙的。当 Lunk 将 $n$ 条无穷的长链缠绕在一起时，美妙的事情就发生了。

Lunk 有 $n$ 条长链，依次编号为 $1..n$，每条长链都是由无穷个小珠子串连而成。首先，他将 $1$ 号长链摆在平面上，就像下面这样：

<center>
```
1
1
1
1
1
1
1
...
```
</center>

然后他将 $2$ 号长链来回缠绕，像这样：

<center>
```
  1 2
2 1  
  1 2
2 1  
  1 2
2 1  
  1 2
...
```
</center>

之后每次放入编号为 $i$ 的长链之前，Lunk 总要将每一行复制 $i - 1$ 遍。例如，上面的作品经过复制就会变成下面的样子：

<center>
```
1 2      1 2
1 2      2 1
1 2      2 1
2 1      2 1
2 1      1 2
2 1      1 2
1 2      1 2
1 2      ...
```
</center>

然后再将 $3$ 号长链缠绕进去：

<center>
```
  1   2 3      3 1   2  
  1 3 2        3 2   1  
3 1   2          2 3 1  
3 2   1          2   1 3
  2 3 1          1   2 3
  2   1 3        1 3 2  
  1   2 3      3 1   2  
  1 3 2           ...   
```
</center>

（请注意，这与缠绕 $2$ 号长链时的方法有所不同）

之后，Lunk 运用同样的方法，将更多的长链缠绕进去。例如，当 $n = 4$ 时，我们应该会得到这样的东西：

<center>
```
1 2 3 4      1 3 4 2      4 3 2 1      2 4 3 1
1 2 4 3      1 3 2 4      3 4 2 1      4 2 3 1
1 4 2 3      3 1 2 4      3 2 4 1      4 2 1 3
4 1 2 3      3 1 4 2      3 2 1 4      2 4 1 3
4 1 3 2      3 4 1 2      2 3 1 4      2 1 4 3
1 4 3 2      4 3 1 2      2 3 4 1        ...  
```
</center>

可 Lunk 终有一天会老去，会记不起自己所创造的美妙的作品，但他还记得某一行的样子。他最后找到了你，想知道他所记得的那一行的下一行是什么样子。

我们可以证明，**你所要回答的东西是唯一的**。并且我们保证 Lunk 的记忆是正确的，即他**所描述的那一行的确在作品中出现过**。

*****

#### 输入格式
从文件 `spiral.in` 输入数据。

第一行输入一个正整数 $n$，表示 Lunk 手上长链的个数。

接下来一行 $n$ 个正整数，表示 Lunk 记忆中的那一行的样子。

#### 输出格式
输出到文件 `spiral.out` 中。

输出一行 $n$ 个正整数，表示 Lunk 记忆中的那一行的下一行的样子。

#### 样例 1
##### 输入
```
4
1 2 3 4
```

##### 输出
```
1 2 4 3
```

#### 样例 2
##### 输入
参见下发文件 `spiral2.in`。

##### 输出
参见下发文件  `spiral2.ans`。

#### 限制与约定
对于 $100\%$ 的数据，满足 $3 \leqslant n \leqslant 10^6$。

对于每个测试点的限制如下：

<table class="detail-table">
<thead>
<tr><th width=50%>测试点编号</th><th>$n$ 的规模</th></thead>
</tr>
<tbody>
<tr><td>$1$</td><td>$= 4$</td></tr>
<tr><td>$2$</td><td rowspan="2">$\leqslant 9$</td></tr>
<tr><td>$3$</td></tr>
<tr><td>$4$</td><td>$\leqslant 100$</td></tr>
<tr><td>$5$</td><td rowspan="2">$\leqslant 1000$</td></tr>
<tr><td>$6$</td></tr>
<tr><td>$7$</td><td rowspan="2">$\leqslant 10^5$</td></tr>
<tr><td>$8$</td></tr>
<tr><td>$9$</td><td rowspan="2">$\leqslant 10^6$</td></tr>
<tr><td>$10$</td></tr>
</tbody>
</table>

*****

### <center>储能树</center>

<br />

#### 题目描述
树是一张 $n$ 个点 $n - 1$ 条边的无向连通图。对于树上的每一条边，Lunk 可以用来存储一定的能量。一条边所能存储的能量的多少是由这棵树上其它边的权值所决定的。具体来讲，我们将一条边删去之后，我们将得到两棵树，记这两棵树的边权之和分别为 $A$ 和 $B$，那么这条边所能存储的能量上限是 $AB$。例如，在下面的这棵树中：

<img width=230px src="https://git.oschina.net/riteme/blogimg/raw/master/other/vnoipday1-2.svg" />

$2$ 号节点和 $4$ 号节点之间的边删去后，剩下两棵树的权值之和分别为 $9$ 和 $3$，所以这条边最多能存储 $9 \times 3 = 27$ 的能量。而 $4$ 号节点和 $6$ 号节点的之间的边删去后，会出现一棵只有一个节点的树，此时的边权之和为 $0$ ，所以这条边无法存储任何能量。

Lunk 的这棵树并不是一成不变的，有时候 Lunk 可能会改变一条边的权值。而你所要做的事情就是在每次变动之后，回答 Lunk 最多能在这棵树上存储多少的能量。

#### 输入格式
从文件 `tree.in` 输入数据。

第一行输入两个正整数 $n$ 和 $q$，表示这棵树的节点个数以及边权变动的次数。

接下来 $n - 1$ 行，每行三个整数 $u$、$v$ 和 $w$，表示一条连接 $u$ 号节点和 $v$ 号节点的边，其权值为 $w$。

接下来 $q$ 行，每行三个整数 $u$、$v$ 和 $w$，表示将 $u$ 号节点和 $v$ 号节点之间的边权改为 $w$。数据保证这条边存在。

#### 输出格式
输出到文件 `tree.out` 中。

输出一共 $q$ 行，表示每次变动之后 Lunk 最多能存储的能量。数据保证这个值小于 $2^{63}$。

#### 样例 1
##### 输入
```
7 4
1 2 2
1 7 1
2 3 2
2 6 1
3 4 1
3 5 1
1 2 2
1 2 3
2 3 3
1 2 0
```

*****

##### 输出
```
13
15
16
10
```

#### 样例 2
##### 输入
参见下发文件 `tree2.in`。

##### 输出
参见下发文件  `tree2.ans`。

#### 限制与约定
对于 $100\%$ 的数据，满足 $n, \; q \leqslant 10^5$，$1 \leqslant u,\;v \leqslant n$，$w \leqslant 10$。

对于每个测试点的限制如下：

<table class="detail-table">
<thead>
<tr><th width=25%>测试点编号</th><th width=25%>$n$ 的规模</th><th width=25%>$q$ 的规模</th><th>特殊限制</th></tr>
</thead>
<tbody>
<tr><td>$1$</td><td>$\leqslant 1000$</td><td rowspan="2">$= 1$</td><td rowspan="4">无特殊限制</td></tr>
<tr><td>$2$</td><td>$\leqslant 10^5$</td></tr>
<tr><td>$3$</td><td rowspan="2">$\leqslant 1000$</td><td rowspan="2">$\leqslant 1000$</td></tr>
<tr><td>$4$</td></tr>
<tr><td>$5$</td><td rowspan="6">$\leqslant 10^5$</td><td rowspan="6">$\leqslant 10^5$</td><td rowspan="2">树是一条链</td></tr>
<tr><td>$6$</td></tr>
<tr><td>$7$</td><td rowspan="4">无特殊限制</td></tr>
<tr><td>$8$</td></tr>
<tr><td>$9$</td></tr>
<tr><td>$10$</td></tr>
</tbody>
</table>
