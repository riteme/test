## <center>将夜</center>
### 题目描述
*“伙计，你看过《将夜》吗？”*
<div style="text-align: right">—— Haogram</div>

<br />

话说宁缺带着病重的桑桑前往烂柯寺修佛养病，奈何桑桑身为冥王之女$^1$的身份被揭穿，于是乎宁缺将携桑桑逃亡。

他们先要破烂柯寺中七念$^2$为了杀他们设下的局，然后前往连绵不绝的岷山，在其中的某处与大黑马$^3$会面，最终逃向荒人$^4$的领地。为了保险，**宁缺不会经过一个地方两次及以上**。

所有地点均被编号为 $1..n$，并有 $m$ 条双向道路。其中烂柯寺编号为 $s$，荒人领地编号为 $t$，大黑马所在的山编号为 $v$，宁缺能否不经过一个地方两次及以上，成功逃至荒人领地？

$5 \times 10^5$个读者眼里有$5 \times 10^5$个宁缺，请你为每个宁缺解开他心中的疑惑。

### 输入格式
从文件`night.in`输入数据。

第一行输入三个正整数 $n$、$m$ 和 $q$，分别表示地点的数量、双向道路的数量以及询问的数量。

接下来 $m$ 行，每行两个正整数 $u$ 和 $v$，表示编号为 $u$ 的地点和编号为 $v$ 的地点之间的一条双向道路。

接下来 $q$ 行，每行三个正整数 $s$、$t$ 和 $v$，表示一次宁缺的询问。

### 输出格式
输出到文件`night.out`中。

输出一行一共 $q$ 个字符，每个字符均为`0`或`1`。如果存在一种合法的方案，则输出`1`，否则输出`0`。

### 输入编码方式
由于输入文件巨大，为了减少输入量，正式输入数据均已编码。具体的编码方式将不在题面中给出，请参见`decoder.cpp`来获得读取输入的方法。

具体的，在`decoder.cpp`中实现了一个`Decoder`类，用于负责文件输入。首先你需要指定`Decoder`读入编码字符串的文件。例如，下面的语句创建了一个从标准输入读入的`Decoder`：

```c++
Decoder *decoder = new Decoder(stdin);
```

使用成员函数`next`可以获得编码后的输入中的下一个`int`整型。例如，下面的语句读入了输入文件的第一个整型 $n$ 和第二个整型 $m$：

```c++
int n = decoder->next();
int m = decoder->next();
```

原输入数据的所有整型均按照输入顺序依次编码。

请注意，一个`Decoder`实例最多占用 $30\mathrm{MB}$ 的内存。

### 样例1
#### 输入
```
4 3 2
1 2
1 3
1 4
2 4 1
2 4 3
```

#### 编码后的输入
```
aaaeaaadaaacaaabaaacaaabaaadaaabaaaeaaacaaaeaaabaaacaaaeaaad
```

#### 输出
```
10
```

### 样例2
#### 编码后的输入
参见下发文件`night2.in`。

#### 输出
参见下发文件`night2.ans`。

### 限制与约定
对于 $100\%$ 的数据，满足 $n \leqslant 5 \times 10^5$，$m \leqslant 10^6$，$q \leqslant 5 \times 10^5$，$1 \leqslant u,\;v,\;s,\;t\leqslant n$。

对于每个测试点的限制如下表：

<table>
<thead>
<tr><td>$n$ 的规模</td><td>$m$ 的规模</td><td>$q$ 的规模</td><td>测试点编号</td><td>特殊限制</td></tr>
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
<tr><td rowspan="14">$\leqslant 500000$</td><td>$= n - 1$</td><td rowspan="14">$\leqslant 500000$</td><td>$12$</td><td rowspan="2">保证是连通图</td></tr>
<tr><td>$= n$</td><td>$13$</td></tr>
<tr><td rowspan="5">$\leqslant 1000000$</td><td>$14$</td><td rowspan="2">每条边只属于一个简单环</td></tr>
<tr><td>$15$</td></tr>
<tr><td>$16$</td><td rowspan="2">数据随机生成</td></tr>
<tr><td>$17$</td></tr>
<tr><td>$18$</td><td>不存在重边和自环</td></tr>
<tr><td>$\leqslant 600000$</td><td>$19$</td><td rowspan="7">无特殊性质</td></tr>
<tr><td>$\leqslant 700000$</td><td>$20$</td></tr>
<tr><td rowspan="5">$\leqslant 1000000$</td><td>$21$</td></tr>
<tr><td>$22$</td></tr>
<tr><td>$23$</td></tr>
<tr><td>$24$</td></tr>
<tr><td>$25$</td></tr>
</tbody>
</table>

**时间限制：** $2\mathrm{s}$

**空间限制：** $512\mathrm{MB}$

### 注记
1. 冥王之女是永夜到来的前兆，永夜时世界一片昏暗毫无生机，故人们惧之而欲杀之。
2. 七念，佛宗天下行走，天下行走即入世者。
3. 大黑马，神骏一匹，通人性，宁缺坐骑。
4. 荒人，信奉冥王，实则恐惧冥王而祈祷其永不到来。

