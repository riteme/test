# 数据结构2019课程PJ1
这是2019年秋季数据结构课程(孙未未老师)Project1的相关资料。

## 问题描述
一个有序数列被交换了k次导致非完全有序。请你在只能询问数组两个元素大小和交换两个数组元素的情况下将数组恢复成有序。成绩由询问元素大小的次数决定，次数越少成绩越好。
详细描述请参照课程下发PPT。

## 环境需求
代码可使用python3和g++编译运行，其他编译器不保证可运行性。C++代码使用C++11规范。

提示：很多程序需要使用命令行附加参数运行。如果是Windows环境，可以在文件夹中按住Shift右击空白处，选择 在此处打开(命令提示符|PowerShell窗口|Linux Shell) ，并在命令行中附带参数执行程序。

## 文件说明
**data**: 数据文件夹。内含一个样例数据0.in。

**datagen.py**: 批量生成数据。如需使用请自行研究。

**header_list.txt**: C和C++允许的头文件列表。对于C的头文件，使用C++风格的写法也是允许的，如允许stdio.h也允许cstdio。

**interactive_runner.py**: 用于两个程序进行交互，如果输入为源文件会自动先对其进行编译。使用格式为`python3 interactive_runner.py [Judger bin/src] [judger args] -- [Solver bin/src] [solver args]`。例如：`python3 interactive_runner.py judger.cpp data/0.in -- solver.c`，会编译两个源文件，选择指定数据给Judger，并连接Judger和Solver进行交互。

**judger.cpp**: 评测程序。如果没有参数输入那么会读取`data/0.in`作为初始数组，否则读取参数指定数据作为初始数组。同时程序会在交互的同时生成log.txt记录Judger和Solver的所有输出，便于调试。

**maker.cpp**: 生成随机数据的程序。接受数组长度n，随机交换次数k，以及可选的随机种子seed三个参数，并直接输出随机生成的数据。提示：使用`maker 5 2 233 > 0.in`即可将数据直接输输出到0.in中。PowerShell用户请注意，需要使用`cmd /c "maker 5 2 233 > 0.in"`否则会生成UTF-16文件Judger无法正常读取。线上测试和最终测试均使用该程序生成数据，但是随机种子不相同且不公开。

**solver.c, solver.cpp**: 两个实例Solver。它们会先询问100000次，然后执行两次交换：`[3 5] [3 4]`，只能够完成和Judger的交互并通过样例。<font color=#ff0000>注意！请仔细阅读示例solver程序及其注释，尤其是读入和输出相关，否则你的程序可能会出现诸如TLE，Reach EOF等不正常的评分！</font>

**test_all.py**: 评测一个文件夹中的所有数据。需要在同文件夹下有interactive_runner.py。需要三个参数：`[data folder] [Judger src/bin] [Solver src/bin]`。例如：`python3 test_all.py data judger.cpp solver.cpp`

## 在线评测
我们在[http://182.61.3.209:14432/](http://182.61.3.209:14432/)提供在线测试。测试使用认证ID进行认证，不设密码。如果ID遗失或者泄露请联系助教换发新ID。只允许使用自己的ID，禁止因为任何原因使用非本人的ID。每日提交次数和提交间隔有限制，请合理利用。
