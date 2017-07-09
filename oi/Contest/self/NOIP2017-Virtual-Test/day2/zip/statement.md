<br />
<br />
<br />
<center><font style="font-size: 35px">NOIP 模拟赛</font></center>
<br />
<center><font style="font-size: 40px">Day 2</font></center>
<br />
<br />
<br />
<br />
<br />
<br />
<table style="width: 100%">
<tr><td width="25%">题目名称</td><td width="25%">微小的数学</td><td width="25%">椰贼斗恶龙</td><td>将夜</td></tr>
<tr><td>英文名称</td><td><code>problem</code></td><td><code>sequence</code></td><td><code>night</code></td></tr>
<tr><td>输入文件</td><td><code>problem.in</code></td><td><code>sequence.in</code></td><td><code>night.in</code></td></tr>
<tr><td>输出文件</td><td><code>problem.out</code></td><td><code>sequence.out</code></td><td><code>night.out</code></td></tr>
<tr><td>时间限制</td><td>$1\mathrm{s}$</td><td>$1.5\mathrm{s}$</td><td>$2\mathrm{s}$</td></tr>
<tr><td>空间限制</td><td>$512\mathrm{MB}$</td><td>$512\mathrm{MB}$</td><td>$512\mathrm{MB}$</td></tr>
<tr><td>测试点个数</td><td>$10$</td><td>$20$</td><td>$25$</td></tr>
<tr><td>单个测试点分值</td><td>$10$</td><td>$5$</td><td>$4$</td></tr>
<tr><td>是否有附加文件</td><td>否</td><td>否</td><td>是</td></tr>
<tr><td>题目类型</td><td>传统型</td><td>传统型</td><td>传统型</td></tr>
<tr><td colspan="4">提交文件需加后缀：</td></tr>
<tr><td>对于 C\+\+ 语言</td><td><code>problem.cpp</code></td><td><code>sequence.cpp</code></td><td><code>night.cpp</code></td></tr>
<tr><td>对于 C 语言</td><td><code>problem.c</code></td><td><code>sequence.c</code></td><td><code>night.c</code></td></tr>
<tr><td>对于 Pascal 语言</td><td><code>problem.pas</code></td><td><code>sequence.pas</code></td><td><code>night.pas</code></td></tr>
<tr><td colspan="4">编译选项：</td></tr>
<tr><td>对于 C\+\+ 语言</td><td><code>-O2 -std=c\+\+11 -lm</code></td><td><code>-O2 -std=c\+\+11 -lm</code></td><td><code>-O2 -std=c\+\+11 -lm</code></td></tr>
<tr><td>对于 C 语言</td><td><code>-O2 -lm</code></td><td><code>-O2 -lm</code></td><td><code>-O2 -lm</code></td></tr>
<tr><td>对于 Pascal 语言</td><td><code>-O2</code></td><td><code>-O2</code></td><td><code>-O2</code></td></tr>
</table>

*****

### <center>微小的数学</center>

<br />

#### 题目描述
*“现在请你追随强者的脚步，来虐掉这个题，做一点微小的数学吧。”*
<div style="text-align: right">—— ruanxingzhi</div>

<br />

组合数 ${n \choose m}$ 表示的是从 $n$ 个物品中选出 $m$ 个物品的方案数。举个例子，从 $\{1,\;2,\;3\}$ 三个物品中选择两个物品可以有 $\{1,\;2\}$，$\{1,\;3\}$，$\{2,\;3\}$ 这三种选择方法。根据组合数的定义，我们可以给出计算组合数 ${n \choose m}$ 的一般公式：

$$ {n \choose m} = {n! \over m!(n - m)!} $$

其中，$n! = 1 \times 2 \times \cdots \times n$。特别的，定义 $0! = 1$。

欧文针针怪 <font style="font-weight: bold">·</font> 穆罕默德 <font style="font-weight: bold">·</font> 买买提想要你，对于给定的 $n$ 和等差数列 $\{a_k\}$，计算下面的和式：

$$ \sum_{k = 0}^n a_k {n \choose k} $$

其中，我们令 $a_0 = s$，并且 $a_n = a_{n - 1} + d, \;\forall n > 0$。

#### 输入格式
从文件 `problem.in` 输入数据。

输入一共一行三个正整数 $n$、$s$ 和 $d$，这些参数的意义均在上文给出。

#### 输出格式
输出到文件 `problem.out` 中。

输出共一行一个整型，表示答案对 $998244353$ 取模后的值。

#### 样例 1
##### 输入
```
9999999 1 0
```

##### 输出
```
951935696
```

##### 解释
机智的鸥蛤菌发现这个数字就是 $2^{9999999} \bmod 998244353$。

#### 样例 2
##### 输入
```
9999999 1000000000000000000 899999999999777777
```

##### 输出
```
348456814
```

*****

#### 限制与约定
对于 $100\%$ 的数据，满足 $n,\;s,\;d \leqslant 10^{18}$。

对于每个测试点的限制如下：

<table class="detail-table">
<thead>
<tr><th width=50%>测试点编号</th><th>$n$ 的规模</th></tr>
</thead>
<tbody>
<tr><td>$1$</td><td>$\leqslant 10$</td></tr>
<tr><td>$2$</td><td rowspan="2">$\leqslant 1000$</td></tr>
<tr><td>$3$</td></tr>
<tr><td>$4$</td><td rowspan="3">$\leqslant 5 \times 10^6$</td></tr>
<tr><td>$5$</td></tr>
<tr><td>$6$</td></tr>
<tr><td>$7$</td><td rowspan="4">$\leqslant 10^{18}$</td></tr>
<tr><td>$8$</td></tr>
<tr><td>$9$</td></tr>
<tr><td>$10$</td></tr>
</tbody>
</table>

*****

### <center>椰贼斗恶龙</center>

<br />

#### 题目描述
*“Zy 是一位在异界闻名的勇士。”*
<div style="text-align: right">—— Link</div>

<br />

Zy 在知道公主 ZY 被恶龙 BigGayY 抓走后，内心及其不平静。

Zy 知道他走向人生巅峰，迎娶公主的时候到了。他要去找到 BigGayY，然后打摆他。

但是，BigGayY 早就知道闻名的勇士 Zy 会来。

因此倾心于他的公主 SAMA 找到了他的骑士们阻止 Zy 的到来。

骑士有 $n$ 个，他们分为高茎和矮茎两种。并且它们很逗逼，会依次按顺序与 Zy 决斗。

作为勇士的 Zy 很强，他每一拳都可以打死一个骑士，或者避开这个骑士。

然而 Zy 发现矮茎的骑士有毒，跟矮茎的骑士决斗之后就会变矮，因而无力击败高茎骑士。

经过 Link 的计算，Zy 已经知道他有很大概率救不出公主了。但他依然要打死**尽可能多的骑士**，以表现自己的英勇。

Zy 记录下了一个数列 $a_i$，表示 Zy 最多能打死 $i$ 个骑士的排列方案数量。由于同种骑士之间是没有区别的，所以**两种排列方案不同当且仅当存在一个位置的骑士种类不同**。

同时，他也非常喜欢奇数。因此他找到了你，想知道 $a_1$ 到 $a_n$ 中哪些数是奇数。

#### 输入格式
从文件 `sequence.in` 中输入数据。

输入共一行一个长度为 $n$ 的仅包含 `0`、`1` 和 `.` 的字符串，表示骑士来临的顺序，靠前的骑士将先与 Zy 决斗。其中 `.` 表示这个位置上既可能是高茎骑士，也可能是矮茎骑士。而 `0` 和 `1` 则分别表示这一位只会是高茎骑士或者矮茎骑士。

#### 输出格式
输出到文件 `sequence.out` 中。

输出一共一行一个仅包括 `0` 和 `1` 的字符串。如果 $a_i$ 为奇数，则第 $i$ 个字符输出 `1`，否则输出 `0`。

#### 样例 1
##### 输入
```
..
```

##### 输出
```
11
```

##### 解释
一共有 $4$ 种骑士来临的方案：

1. `00`：Zy 最多打死 $2$ 个骑士。
2. `01`：Zy 最多打死 $2$ 个骑士。
3. `10`：Zy 最多打死 $1$ 个骑士。
4. `11`：Zy 最多打死 $2$ 个骑士。

因此我们可以得到 $a_1 = 1$ 和 $a_2 = 3$，它们都是奇数，所以输出 `11`。

*****

#### 样例 2
##### 输入
```
.1..1.11..1010....
```

##### 输出
```
000000001110001000
```

##### 解释
机智的 Zy 发现了一个吉利的数字：$11111010_{(2)} = 250_{(10)}$

#### 限制与约定
对于 $100\%$ 的数据，满足 $1 \leqslant n \leqslant 2000$。

对于每个测试点的限制如下：

<table class="detail-table">
<thead>
<tr><th width=50%>测试点编号</th><th>$n$ 的规模</th></tr>
</thead>
<tbody>
<tr><td>$1$</td><td rowspan="4">$\leqslant 20$</td></tr>
<tr><td>$2$</td></tr>
<tr><td>$3$</td></tr>
<tr><td>$4$</td></tr>
<tr><td>$5$</td><td>$\leqslant 50$</td></tr>
<tr><td>$6$</td><td>$\leqslant 100$</td></tr>
<tr><td>$7$</td><td>$\leqslant 200$</td></tr>
<tr><td>$8$</td><td>$\leqslant 300$</td></tr>
<tr><td>$9$</td><td>$\leqslant 400$</td></tr>
<tr><td>$10$</td><td rowspan="2">$\leqslant 500$</td></tr>
<tr><td>$11$</td></tr>
<tr><td>$12$</td><td rowspan="2">$\leqslant 1000$</td></tr>
<tr><td>$13$</td></tr>
<tr><td>$14$</td><td rowspan="2">$\leqslant 1500$</td></tr>
<tr><td>$15$</td></tr>
<tr><td>$16$</td><td rowspan="5">$\leqslant 2000$</td></tr>
<tr><td>$17$</td></tr>
<tr><td>$18$</td></tr>
<tr><td>$19$</td></tr>
<tr><td>$20$</td></tr>
<tbody>
</table>

*****

### <center>将夜</center>

<br />

#### 题目描述
*“伙计，你看过《将夜》吗？”*
<div style="text-align: right">—— Haogram</div>

<br />

话说宁缺带着病重的桑桑前往烂柯寺修佛养病，奈何桑桑身为冥王之女$^1$的身份被揭穿，于是乎宁缺将携桑桑逃亡。

他们先要破烂柯寺中七念$^2$为了杀他们设下的局，然后前往连绵不绝的岷山，在其中的某处与大黑马$^3$会面，最终逃向荒人$^4$的领地。为了保险，**宁缺不会经过一个地方两次及以上**。

所有地点均被编号为 $1..n$，并有 $m$ 条双向道路。其中烂柯寺编号为 $s$，荒人领地编号为 $t$，大黑马所在的山编号为 $v$，宁缺能否不经过一个地方两次及以上，成功逃至荒人领地？

$5 \times 10^5$ 个读者眼里有 $5 \times 10^5$ 个宁缺，请你为每个宁缺解开他心中的疑惑。

#### 输入格式
从文件 `night.in` 输入数据。

第一行输入三个正整数 $n$、$m$ 和 $q$，分别表示地点的数量、双向道路的数量以及询问的数量。

接下来 $m$ 行，每行两个正整数 $u$ 和 $v$，表示编号为 $u$ 的地点和编号为 $v$ 的地点之间的一条双向道路。

接下来 $q$ 行，每行三个正整数 $s$、$t$ 和 $v$，表示一次宁缺的询问。

#### 输出格式
输出到文件 `night.out` 中。

输出一行一共 $q$ 个字符，每个字符均为 `0` 或 `1`。如果存在一种合法的方案，则输出 `1`，否则输出 `0`。

#### 输入编码方式
由于输入文件巨大，为了减少输入量，正式输入数据均已编码。具体的编码方式将不在题面中给出，请参见 `decoder.cpp` 来获得读取输入的方法。

具体的，在 `decoder.cpp` 中实现了一个 `Decoder` 类，用于负责文件输入。首先你需要指定 `Decoder` 读入编码字符串的文件。例如，下面的语句创建了一个从标准输入读入的 `Decoder`：

```c++
Decoder *decoder = new Decoder(stdin);
```

使用成员函数 `next` 可以获得编码后的输入中的下一个 `int` 整型。例如，下面的语句读入了输入文件的第一个整型 $n$ 和第二个整型 $m$：

```c++
int n = decoder->next();
int m = decoder->next();
```

原输入数据的所有整型均按照输入顺序依次编码。

请注意，一个 `Decoder` 实例最多占用 $30\mathrm{MB}$ 的内存。

*****

#### 样例 1
##### 输入
```
4 3 2
1 2
1 3
1 4
2 4 1
2 4 3
```

##### 编码后的输入
```
aaaeaaadaaacaaabaaacaaabaaadaaabaaaeaaacaaaeaaabaaacaaaeaaad
```

##### 输出
```
10
```

#### 样例 2
##### 编码后的输入
参见下发文件 `night2.in`。

##### 输出
参见下发文件 `night2.ans`。

*****

#### 限制与约定
对于 $100\%$ 的数据，满足 $n \leqslant 5 \times 10^5$，$m \leqslant 10^6$，$q \leqslant 5 \times 10^5$，$1 \leqslant u,\;v,\;s,\;t\leqslant n$。

对于每个测试点的限制如下：

<table class="detail-table">
<thead>
<tr><th width=20%>$n$ 的规模</th><th width=20%>$m$ 的规模</th><th width=20%>$q$ 的规模</th><th width=20%>测试点编号</th><th>特殊限制</th></tr>
</thead>
<tbody>
<tr><td>$= 10$</td><td>$= 15$</td><td>$= 1$</td><td>$1$</td><td rowspan="11">无特殊性质</td></tr>
<tr><td>$\leqslant 100$</td><td>$\leqslant 300$</td><td rowspan="7">$\leqslant 10$</td><td>$2$</td></tr>
<tr><td rowspan="2">$\leqslant 1000$</td><td>$\leqslant 2000$</td><td>$3$</td></tr>
<tr><td>$\leqslant 3000$</td><td>$4$</td></tr>
<tr><td rowspan="7">$\leqslant 100000$</td><td rowspan="2">$\leqslant 200000$</td><td>$5$</td></tr>
<tr><td>$6$</td></tr>
<tr><td rowspan="2">$\leqslant 300000$</td><td>$7$</td></tr>
<tr><td>$8$</td></tr>
<tr><td>$\leqslant 200000$</td><td rowspan="3">$\leqslant 100000$</td><td>$9$</td></tr>
<tr><td rowspan="2">$\leqslant 300000$</td><td>$10$</td></tr>
<tr><td>$11$</td></tr>
<tr><td rowspan="14">$\leqslant 500000$</td><td>$= n - 1$</td><td rowspan="14">$\leqslant 500000$</td><td>$12$</td><td rowspan="2">保证任意两个地点之间均有路径相互可到达</td></tr>
<tr><td>$= n$</td><td>$13$</td></tr>
<tr><td rowspan="5">$\leqslant 1000000$</td><td>$14$</td><td rowspan="2">每条双向道路最多被一条简单回路覆盖</td></tr>
<tr><td>$15$</td></tr>
<tr><td>$16$</td><td rowspan="2">数据随机生成</td></tr>
<tr><td>$17$</td></tr>
<tr><td>$18$</td><td>没有重边和自环</td></tr>
<tr><td>$\leqslant 600000$</td><td>$19$</td><td rowspan="7">无特殊性质</td></tr>
<tr><td>$\leqslant 700000$</td><td>$20$</td></tr>
<tr><td rowspan="5">$\leqslant 1000000$</td><td>$21$</td></tr>
<tr><td>$22$</td></tr>
<tr><td>$23$</td></tr>
<tr><td>$24$</td></tr>
<tr><td>$25$</td></tr>
</tbody>
</table>

*****

#### 注记
1. 冥王之女是永夜到来的前兆，永夜时世界一片昏暗毫无生机，故人们惧之而欲杀之。
2. 七念，佛宗天下行走，天下行走即入世者。
3. 大黑马，神骏一匹，通人性，宁缺坐骑。
4. 荒人，信奉冥王，实则恐惧冥王而祈祷其永不到来。

