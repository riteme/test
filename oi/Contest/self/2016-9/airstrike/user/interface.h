#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <cstddef>

// 请按照要求完成下列三个函数。

/**
 * 载入程序
 * @param x  一个double数组，存储了所有顶点的x坐标
 * @param y  一个double数组，存储了所有顶点的y坐标
 * @param n  顶点个数
 * @param id 数据点编号
 * @remark:
 *     所有顶点互不相同，并且按照逆时针给出。
 *     温馨提示：数组下标从0开始。
 *     PS: 请不要尝试利用数组越界来达到某些目的，后果自负。
 */
extern void initialize(const double *x, const double *y, const size_t n,
                       const int id);

/**
 * 查询操作
 * @param  dx 查询的点的x坐标
 * @param  dy 查询的点的y坐标
 * @return    按照要求返回true或false
 */
extern bool query(const double dx, const double dy);

/**
 * 结束程序
 * @remark:
 *     请不要将在initialize中给你的数组使用delete[]删除，
 *     否则将导致程序崩溃。
 */
extern void finalize();

#endif  // INTERFACE_H_
