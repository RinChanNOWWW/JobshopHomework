/**
 * base of GA
 * 
 * gene.h
 * by Hzy
 * 2018-5-10
 */

#pragma once

#ifndef _GENE_H_
#define _GENE_H_

#include "base.h"

#define Max_Length 300            //编码染色体的最大长度
#define Max_Population 300        //最大种群数量
#define Px 0.95                   //染色体交叉概率
#define Pm 0.25                   //染色体变异概率
#define ITERATE 1500              //种群进化（迭代）次数

/**
 * 创建一个编码染色体
 *
 * require 作业需求结构体
 * all_operation 总工序数
 * return 指向此染色体的指针
 */
int * creatChromo(All_job require, int all_operation);

/**
 * 创建并初始化一个种群
 * 
 * require 作业需求结构体
 * all_operation 指向总工序数的指针
 * return 指向此种群的指针
 */
int** newPopulation(All_job require, int* all_operation);

/**
 * 销毁种群
 * 
 * population 指向一个种群的指针
 */
void deletePopulation(int** population);

/**
 * 更新种群（进化）
 *
 * oldpopulation 指向老种群（父代（的指针
 * machine 总机器数
 * job 总工件数
 * all_operation 总工序数
 * return 指向新种群（子代）的指针
 */
int** nextPopulation(int** oldpopulation, int machine, int job, int all_operation);

/**
 * 计算此编码染色体对应的加工时间
 *
 * chromo[] 编码染色体
 * all_operation 总工序数
 * return 加工时间
 */
int getCmax(int* chromo, int all_operation);

/**
 * 染色体交叉（改进版）
 *
 * p1 父代1染色体
 * p2 父代2染色体
 * all_operation 总工序数
 */
void order_crossover(int* p1, int* p2, int all_operation);

/**
 * 染色体变异
 *
 * chromo[] 要变异的编码染色体
 * all_operation 总工序数
 */
void mutation(int* chromo, int all_operation);

/**
 * 产生一个轮赌盘
 * 
 * population 种群
 * all_operation 总工序数
 * return 轮赌盘-一个概率数组
 */
double* roulette(int** population, int all_operation);

#endif // !_GENE_H_
