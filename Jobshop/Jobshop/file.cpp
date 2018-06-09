/**
 * def of file.h
 *
 * file.c
 * by 何哲宇
 * 2018-5-14
 */
#pragma once

#include<stdio.h>
#include <string.h>
#include <time.h>
#include "file.h"
#include "gene.h"

int MachineNum[MAX_MATRIX][MAX_MATRIX];       //工件i第j道工序加工所用的机器号
int Time[MAX_MATRIX][MAX_MATRIX];             //工件i第j道工序加工所用时间
extern int best_fitness;                      //最优解
extern clock_t start, end;

/**  没有按要求输入的临时调试输入函数
void input(All_job * job)
{
	scanf("%d %d", &((*job).job_amount), &((*job).machine_amount));
	int i;
	for (i = 0; i < (*job).job_amount; i++)
		scanf("%d", &((*job)).operation_amount[i]);
	int j;
	for (i = 1; i <= (*job).job_amount; i++)
		for (j = 1; j <= (*job).operation_amount[i - 1]; j++)
			scanf("%d %d", &MachineNum[i][j], &Time[i][j]);
}
*/

/**
 * 从文件（可选从键盘/stdin）中读取需要的数据
 *
 * job 存储所有基本数据的结构体类型
 */
void read_from_file(All_job * job)
{
//	int opt;                            //选择类型
	FILE * fp;        
	/* 基本文件操作部分 */
	fp = fopen("input.txt", "r");
//	printf("从文件/键盘输入？\n");
//	printf("输入1从文件输入，2从键盘输入:\n");
/*	scanf("%d", &opt);
	if (opt == 2) {
		fp = stdin;                     //若选择从键盘输入，则将文件输入流改为标准输入流stdin
		printf("请输入数据:\n");
	}*/
	/* 读取数据部分 */
	fscanf(fp, "%d %d", &(*job).job_amount, &(*job).machine_amount);     
/*	int count = 0;
	int jobNum;
	while ((fscanf(fp, "%d", &jobNum) == 1) && jobNum != -1) {
		count = 0;                           //记录此工件一共有几道工序
		int operation = 1;                   //记录此工序为工件的第几道工序
		char ch;*/
		/* 处理每行输入数据 */
/*		while ((ch = fgetc(fp)) != '\n') {
			if (ch == ' ')                   //忽略空格
				continue;
			else if (ch == ')')              //忽略括号 
				continue;
			else if (ch == '(') {            //忽略括号
				count++;
				fscanf(fp, "%d", &Time[jobNum][operation]);
				fgetc(fp);
				fscanf(fp, "%d", &MachineNum[jobNum][operation]) ;
				operation++;
			}
		}
		(*job).operation_amount[jobNum - 1] = count;
	}*/
	int i, j;
	int M, T;
	for (i = 1; i <= job->job_amount; i++) {
		for (j = 1; j <= job->machine_amount; j++) {
			fscanf(fp, "%d %d", &M, &T);
			MachineNum[i][j] = M + 1;
			Time[i][j] = T;
		}
		job->operation_amount[i - 1] = job->machine_amount;
	}
	/* 关闭文件 */
	fclose(fp);
}

/**
 * 输出计算结果
 *
 * elite[] 最优解所对应的编码染色体
 * machine 总机器数
 * job 总工件数
 * all_operation 总工序数
 */
void output(int * elite, int machine, int job, int all_operation)
{
	/* 基本文件操作 */
	FILE * fp;
	fp = fopen("output.txt", "w");
	/* 创建一个记录输出数据信息的二维数组 */
	Result result[MAX_MATRIX][MAX_MATRIX];         //机器i上第j道工序
	/* 初始化结果数组 */
	int i, j;
	for (i = 0; i <= machine; i++)
		for (j = 0; j <= job; j++) {
			Result temp = { -1, -1, -1, -1 };
			result[i][j] = temp;
		}
	/* 计算结果结构体所需要的数据 */
	int machineEndTime[Max_Length];                //机器i上做完最新工序的时间
	int jobEndTime[Max_Length];                    //工件i做完最新工序的时间 
	int index[Max_Length];                         //最新工序在工件中的序号
	/* 初始化清零 */
	memset(machineEndTime, 0, Max_Length);
	memset(jobEndTime, 0, Max_Length);
	memset(index, 0, Max_Length);
	/* 计算所需要的变量 */
	int jobNum;                                    //该工序所在工件号
	int operationNum;                              //该工序是工件的第几道工序
	int machineNum;                                //该工序所在机器号
	int begin;                                     //该工序的开始时间
	int end;                                       //该工序的结束时间
	/* 按顺序遍历编码染色体，逐工件操作 */
	for (i = 0; i < all_operation; i++) {
		jobNum = elite[i];
		index[jobNum]++;
		operationNum = index[elite[i]];
		machineNum = MachineNum[jobNum][operationNum];
		begin = machineEndTime[machineNum] > jobEndTime[jobNum] ? machineEndTime[machineNum] : jobEndTime[jobNum];
		end = begin + Time[jobNum][operationNum];
		machineEndTime[machineNum] = end;
		jobEndTime[jobNum] = end;
		j = 0;
		/* 按顺序找到该机器的结果数组中没有数据的位置 */
		while (result[machineNum][j].begin != -1)
			j++;
		/* 输入结果 */
		result[machineNum][j].begin = begin;
		result[machineNum][j].end = end;
		result[machineNum][j].job = jobNum;
		result[machineNum][j].operation = operationNum;
	}
	/* 打印结果 */
	for (i = 0; i <= machine; i++) {     //遍历每个机器的结果序列
		/* 从有数据的位置开始 */
		if (result[i][0].begin == -1)
			continue;
		printf("M%d", i - 1);               //到屏幕
		fprintf(fp, "M%d", i - 1);          //到文件
		/* 逐列读取 */
		for (j = 0; j < job; j++) {
			if (result[i][j].begin == -1)     //到没有数据的位置结束
				break;
			printf(" (%d,%d-%d,%d)", result[i][j].begin, result[i][j].job - 1, result[i][j].operation - 1, result[i][j].end);
			fprintf(fp, " (%d,%d-%d,%d)", result[i][j].begin, result[i][j].job - 1, result[i][j].operation - 1, result[i][j].end);
		}
		printf("\n");
		fprintf(fp, "\n");
	}
	printf("End %d\n", best_fitness);
	fprintf(fp, "End %d\n", best_fitness);
	fprintf(fp, "Time used:%.3lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	fclose(fp);
}