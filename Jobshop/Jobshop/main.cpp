/**
 * main
 *
 * main.c
 *
 * by Hzy
 * 2018-5-14
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "file.h"
#include "gene.h"

/* 见file.cpp */
extern int MachineNum[MAX_MATRIX][MAX_MATRIX];
extern int Time[MAX_MATRIX][MAX_MATRIX];
/* 见gene.cpp */
extern int best_fitness;
extern int elite;

int main(void)
{
	srand(clock());             //产生一个计算机时间（毫秒为单位）的种子来生成随机数
	/* 计算运行整个程序需要的时间 */
	clock_t start, end;         
	double t;         

	All_job job;      //记录输入的数据
	start = clock();
	read_from_file(&job);
	int i;
	int** Population;
	int all_operation;
	/* 初始化种群 */
    Population = newPopulation(job, &all_operation);
	/* 进化（迭代） */
	for (i = 1; i <= ITERATE; i++) 
		Population = nextPopulation(Population, job.machine_amount, job.job_amount, all_operation);
	/* 输出计算结果 */
	printf("结果输出如下:\n");
	output(Population[elite], job.machine_amount, job.job_amount, all_operation);
	deletePopulation(Population);
	/* 输出程序运行时间 */
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%lf", t);
	system("pause");
	return 0;
}