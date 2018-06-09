/**
 * 此程序需要的基本的数据结构与函数操作
 *
 * base.h
 * by 何哲宇
 * 2018-5-10
 */

#ifndef _BASE_H_
#define _BASE_H_

#define MAX_MATRIX 150      //矩阵的最大规模

/* 存储输入的基本数据 */
typedef struct {
	int machine_amount;              //总共需要的机器个数
	int job_amount;                  //总共的工件个数
	int operation_amount[MAX_MATRIX];   //每个工件的工序数
} All_job;

/* 存储输出的基本数据（单个工序的） */
typedef struct {
	int begin;                       //工序加工的开始时间
	int end;                         //工序加工的结束时间
	int job;                         //该工序所属工件
	int operation;                   //该工序是此工件的第几道工序
} Result;


/**
 * 交换两个数
 * 
 * a 被交换的数
 * b 另一个被交换的数
 */
void exchange(int* a, int* b);

/**
 * 随机打乱一个数组
 * 
 * a[] 将要被打乱的数组
 * n 数组中有效数据的个数
 */
void random_shuffle(int* a, int n);

/**
 * 求两个数的最大值
 * 
 * a 一个数
 * b 另一个数
 * return a与b中的较大值
 */
int getMax(int a, int b);

/**
 * 将一个整数数组复制到另一个整数数组中
 *
 * destination[] 复制产生的数组
 * source[] 被复制的数组
 * n 数组的规模
 */
void arrayCopy(int * destination, int * source, int n);

#endif // !_BASE_H_
