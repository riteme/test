/**
 * 初始化你的程序
 * @param n (int) MHA集团的数量
 * @param q (int) 总共的天数
 */
void initialize(int n, int q);

/**
 * 添加线路
 * @param u (int) 第一个MHA集团
 * @param v (int) 第二个MHA集团
 * @param t (int) 该通信线路的寿命
 */
void add_connection(int u, int v, int t);

/**
 * 询问Lunk最少要多少间谍才可以监听所有的MHA集团
 * @return (int) 返回这个问题的答案
 */
int query();

/**
 * 结束程序
 */
void finalize();
