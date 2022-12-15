A Abstract Picture

题意：有一个 $n×n$ 的方阵，有一些格子上已经指定了颜色，其余的格子则无所谓是什么颜色。现在要求把每一行和每一列按照一定顺序分别染色，要求构造一个顺序使得最终的结果满足一开始指定的要求。

题解：考虑倒着做，则一开始找一行或者一列颜色完全相同的，然后将这一行或者一列删去，最后倒序输出即可。



C Constant Ratio

题意：给定$n$，问有多少个整数等比数列的和为 $n$。

题解：枚举数列的第一项和公比即可。



D dir -C

题意：有一些长度不等的文件名要显示，显示的方式是选择一个行数 $L$，然后每连续的$L$个文件名作为一列显示。最后一列可能不满$L$个文件名。现设定一个显示的最大宽度$w$，问$L$的最小值。

题解：枚举$L$后，用ST表算最小值，检查是否合法即可。



L Liesbeth and the String

题意：初始给一个字符串，内容是 $n$ 个字符`a`，之后反复执行以下操作：

* 如果第一个字符是 `a`，则删掉前两个字符，末尾加上 `bc`。
* 如果是 `b`，删掉头两个，末尾加上 `a`。
* 如果是 `c`，删掉头两个，末尾加上 `aaa`。

问最终要多少次操作才能变成只剩一个字符。

题解：如果当前长度为 $2n$，则下一步的长度为 $n$。如果为 $2n+1$，下一步为 $3n+2$。之后模拟即可。