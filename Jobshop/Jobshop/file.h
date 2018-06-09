/**
 * file and io
 *
 * file.h
 * by 顾希之
 * 2018-5-12
 */
#pragma once
#ifndef _FILE_H_
#define _FILE_H_

#include "base.h"

/** 没有按要求输入的临时调试输入函数
void input(All_job * job);       
*/

/**
 * 从文件（可选从键盘/stdin）中读取需要的数据
 *
 * job 存储所有基本数据的结构体类型
 */
void read_from_file(All_job * job);

/**
 * 输出计算结果
 *
 * elite[] 最优解所对应的编码染色体
 * machine 总机器数
 * job 总工件数
 * all_operation 总工序数
 */
void output(int * elite, int machine, int job, int all_operation);

#endif // !_FILE_H_