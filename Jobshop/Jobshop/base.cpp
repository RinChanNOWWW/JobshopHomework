/**
 * def of base.h
 *
 * base.c
 * by 何哲宇
 * 2018-5-10
 */

#include <time.h>
#include <stdlib.h>
#include "base.h"
#include "gene.h"

extern int best_fitness;              //最优解

/**
 * 交换两个数
 * 
 * a 被交换的数
 * b 另一个被交换的数
 */
void exchange(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * 求两个数的最大值
 *
 * a 一个数
 * b 另一个数
 * return a与b中的较大值
 */
int getMax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

/**
 * 随机打乱一个数组
 *
 * a[] 将要被打乱的数组
 * n 数组中有效数据的个数
 */
void random_shuffle(int* a, int n)
{
	int index, i;
	for (i = 0; i < n; i++) {
		index = rand() % (n - i) + i;          //随机产生被交换的位置
		if (index != i) {
			exchange(&a[i], &a[index]);
		}
	}
}

/**
 * 将一个整数数组复制到另一个整数数组中
 *
 * destination[] 复制产生的数组
 * source[] 被复制的数组
 * n 数组的规模
 */
void arrayCopy(int * destination, int * source, int n)
{
	int i;
	for (i = 0; i < n; i++)
		destination[i] = source[i];
}