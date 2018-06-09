/**
 * def of gene.h
 *
 * gene.c
 * by 何哲宇
 * 2018-5-12
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "gene.h"

extern int MachineNum[MAX_MATRIX][MAX_MATRIX];     //见file.cpp
extern int Time[MAX_MATRIX][MAX_MATRIX];           //见file.cpp
int Cmax[Max_Length];                              //一个种群每个个体的加工时间
long long Cmax_sum;                                      //总加工时间
int best_fitness = INT_MAX;                        //最优解
int elite;                                         //精英所在位置
int Cmax_max;
int elite_chromo[Max_Length];

/**
 * 创建一个编码染色体
 *
 * require 作业需求结构体
 * all_operation 总工序数
 * return 指向此染色体的指针
 */
int * creatChromo(All_job require, int all_operation)
{
	/* 根据输入的数据编码 */
	int* chromo = (int *)malloc(sizeof(int) * all_operation);
	int i, j, k = 0;
	for (i = 0; i < require.job_amount; i++)
		for (j = 0; j < require.operation_amount[i]; j++) {
			chromo[k] = i + 1;
			k++;
		}
	return chromo;
}

/**
 * 创建并初始化一个种群
 *
 * require 作业需求结构体
 * all_operation 指向总工序数的指针
 * return 指向此种群的指针
 */
int** newPopulation(All_job require, int* all_operation)
{
	*all_operation = 0;     //初始化清零
	int i, k = 0;
	for (i = 0; i < require.job_amount; i++)
		*all_operation += require.operation_amount[i];
	int* chromo = NULL;
	int** population = (int **)malloc(sizeof(int *) * Max_Population);
	for (i = 0; i < Max_Population; i++) {
		chromo = creatChromo(require, *all_operation);     //产生一个染色体
		random_shuffle(chromo, *all_operation);            //随机打乱这个染色体
		population[i] = chromo;                            //录入种群
	}
	return population;
}

/**
 * 销毁种群
 *
 * population 指向一个种群的指针
 */
void deletePopulation(int** population)
{
	/* free一个二维数组 */
	int i;
	for (i = 0; i < Max_Population; i++)
		free(population[i]);
	free(population);
}

/**
 * 更新种群（进化）
 *
 * oldpopulation 指向老种群（父代（的指针
 * machine 总机器数
 * job 总工件数
 * all_operation 总工序数
 * return 指向新种群（子代）的指针
 */
int** nextPopulation(int** oldpopulation, int machine, int job, int all_operation)
{
	memset(Cmax, 0, Max_Population); //初始化清零 
	int i, j;
	/* 动态生成新种群的二位数组 */
	int** nextPopulation;
	nextPopulation = (int**)malloc(sizeof(int*) * Max_Population);
	for (i = 0; i < Max_Population; i++)
		nextPopulation[i] = (int *)malloc(sizeof(int) * all_operation);
	/* 生成加工时间（适应度）数组 */
	Cmax_sum = 0;
	int runtime;
	for (i = 0; i < Max_Population; i++) {
		Cmax[i] = getCmax(oldpopulation[i], all_operation);
		Cmax_sum = Cmax_sum + Cmax[i];
		if (Cmax[i] < best_fitness) {        //选出精英
			best_fitness = Cmax[i];          //更新最优解
			elite = i;
			arrayCopy(elite_chromo, oldpopulation[i], all_operation);
		}
		if (Cmax[i] > Cmax_max)
			Cmax_max = Cmax[i];
	}
	/* 保留精英 */
	arrayCopy(nextPopulation[0], oldpopulation[elite], all_operation);
	/* 产生轮赌盘 */
	double * P = roulette(oldpopulation, all_operation);
	/* 利用轮赌盘从老种群（父代）选择子代录入新种群（子代） */
	double pick;     //选择概率
	for (i = 1; i < Max_Population; i++) {     //精英不被操作
		int flag = 0;
		pick = ((double)rand()) / RAND_MAX;    //随机生成概率
		for (j = 0; j < Max_Population; j++) {
			if (pick < P[j]) {
				arrayCopy(nextPopulation[i], oldpopulation[j], all_operation);
				flag = 1;
				break;
			}
		}
		if (flag == 0)    //如果有遗漏则录入精英
			arrayCopy(nextPopulation[i], oldpopulation[elite], all_operation);
	}
	/* 销毁轮赌盘 */
	free(P);
	/* 按概率交叉 */
	double p;
	int choice, cnt = 0;
	for (i = 1; i < Max_Population ; i = i + 1) {
		p = ((double)rand()) / RAND_MAX;       //随机生成交叉概率
		if (p < Px) {   /* 前后两两交叉 */
			cnt++;
			if (cnt % 2 == 0)
				order_crossover(nextPopulation[i], nextPopulation[choice], all_operation);
			else
				choice = i;
		}
			
	}
	/* 按概率变异 */
	for (i = 1; i < Max_Population; i++) {
		p = ((double)rand()) / RAND_MAX;
		if (p < Pm)
			mutation(nextPopulation[i], all_operation);
	}
	/* 销毁老种群（父代） */
	deletePopulation(oldpopulation);
	/* 返回新种群（子代） */
	return nextPopulation;
}

/**
 * 计算此编码染色体对应的加工时间
 *
 * chromo[] 编码染色体
 * all_operation 总工序数
 * return 加工时间
 */
int getCmax(int* chromo, int all_operation)
{
	/* 同file.cpp中函数output_to_file中的初始解码操作 */
	int machineEndTime[Max_Length];
	int jobEndTime[Max_Length];
	int index[Max_Length];
	memset(machineEndTime, 0, Max_Length);
	memset(jobEndTime, 0, Max_Length);
	memset(index, 0, Max_Length);
	int Cmax = 0;
	int jobNum;
	int operationNum;
	int machineNum;
	int begin;
	int end;	
	int i;
	for (i = 0; i < all_operation; i++) {
	
		jobNum = chromo[i];
		index[jobNum]++;
		operationNum = index[chromo[i]];
		machineNum = MachineNum[jobNum][operationNum];
		/* 找出机器最新时间和工件最新时间的最大值 */
		begin = machineEndTime[machineNum] > jobEndTime[jobNum] ? machineEndTime[machineNum] : jobEndTime[jobNum];
		end = begin + Time[jobNum][operationNum];
		/* 更新 */
		machineEndTime[machineNum] = end;
		jobEndTime[jobNum] = end;
		if (Cmax < end)
			Cmax = end;
	}
	return Cmax;
}

/**
 * 染色体交叉（改进版）
 *
 * p1 父代1染色体
 * p2 父代2染色体
 * all_operation 总工序数
 */
void order_crossover(int* p1, int* p2, int all_operation)
{
	
	int i, j, k;
	int* child1 = NULL;
	int* child2 = NULL;
	child1 = (int *)malloc(sizeof(int) * all_operation);
	child2 = (int *)malloc(sizeof(int) * all_operation);
	i = rand() % all_operation;  //随机产生交叉位置
	j = rand() % all_operation;  //随机产生交叉位置
	int head1 = 0;
	int head2 = 0;
	/* 交叉（伪） */
	for (k = i; k < all_operation; k++) {
		child1[head1++] = p1[k];
	}
	for (k = j; k < all_operation; k++) {
		child2[head2++] = p2[k];
	}
	for (k = 0; k < i; k++)
		child1[head1++] = p1[k];
	for (k = 0; k < j; k++)
		child2[head2++] = p2[k];
	arrayCopy(p1, child1, all_operation);
	arrayCopy(p2, child2, all_operation);
	/* 释放内存 */
	free(child1); free(child2); 

}

/**
 * 染色体变异
 *
 * chromo[] 要变异的编码染色体
 * all_operation 总工序数
 */
void mutation(int* chromo, int all_operation)
{
	int i, j;
	/* 随机产生变异位置 */
	i = rand() % all_operation;   
	j = rand() % all_operation;
	while (i == j || chromo[i] == chromo[j]) {
		i = rand() % all_operation;
	}
	/* 交换随机产生的位置的编码完成随机变异 */
	exchange(&chromo[i], &chromo[j]);
}

/**
 * 产生一个轮赌盘
 *
 * population 种群
 * all_operation 总工序数
 * return 轮赌盘-一个概率数组
 */
double* roulette(int** population, int all_operation)
{
	/**
	 * 因为加工时间越短适应度越高
	 * 所有以一个加工时间到适应度的映射产生轮赌盘
	 * 以总加工时间与单个工序加工时间的差作为轮赌盘元素
	 * 按比例计算出每个对应的概率
	 */
	double* P = (double*)malloc(sizeof(double) * Max_Population);
	/* 初始化 */
	memset(P, 0, sizeof(P));
	int ave;
	int i;
	int temp;
	int fitness[Max_Length] = { 0 };
	int fit_sum = 0;
	ave = Cmax_sum / Max_Population;
	temp = -1 * (ave - Cmax_max) + ave / 10;
	
	for (i = 0; i < Max_Population; i++) {
		fitness[i] = ave - Cmax[i] + temp;
//		fitness[i] = exp((double)Cmax[i]);
		fit_sum += fitness[i];
	}
	double recordfit[Max_Length] = { 0 };
	for (i = 0; i < Max_Population; i++) {
		recordfit[i] = (double)fitness[i] / fit_sum;
		if (i == 0)
			P[i] = recordfit[i];
		else
			P[i] = P[i - 1] + recordfit[i];
	}
	
	//int Cmax_sum_differ;     //总的差 
	//Cmax_sum_differ = (Max_Population - 1) * Cmax_sum;
	//P[0] = ((double)(Cmax_sum - Cmax[0])) / Cmax_sum_differ;
	for (i = 0; i < Max_Population; i++) {
	//	P[i] = P[i - 1] + ((double)(Cmax_sum - Cmax[i])) / Cmax_sum_differ;
	}

	return P;
}