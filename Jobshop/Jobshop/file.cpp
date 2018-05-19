/**
 * def of file.h
 *
 * file.c
 * by Hzy
 * 2018-5-14
 */
#pragma once
#include<stdio.h>
#include <string.h>
#include "file.h"
#include "gene.h"

int MachineNum[MAX_MATRIX][MAX_MATRIX];
int Time[MAX_MATRIX][MAX_MATRIX];
extern int best_fitness;

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

void read_from_file(All_job * job)
{
	int opt;
	FILE * fp;
	fp = fopen("input.txt", "r");
	printf("从文件/键盘输入？\n");
	printf("输入1从文件输入，2从键盘输入:\n");
	scanf("%d", &opt);
	if (opt == 2) {
		fp = stdin;
		printf("请输入数据:\n");
	}
	fscanf(fp, "%d %d", &(*job).job_amount, &(*job).machine_amount);
	int count = 0;
	int jobNum;
	while ((fscanf(fp, "%d", &jobNum) == 1) && jobNum != -1) {
		count = 0;
		int operation = 1;
		char ch;
		while ((ch = fgetc(fp)) != '\n') {
			if (ch == ' ')
				continue;
			else if (ch == ')')
				continue;
			else if (ch == '(') {
				count++;
				fscanf(fp, "%d", &Time[jobNum][operation]);
				fgetc(fp);
				fscanf(fp, "%d", &MachineNum[jobNum][operation]) ;
				operation++;
			}
		}
		(*job).operation_amount[jobNum - 1] = count;
	}
	fclose(fp);
}


void output_to_file(int * elite, int machine, int job, int all_operation)
{
	FILE * fp;
	fp = fopen("output.txt", "w");


	fprintf(fp, "End %d\n", best_fitness);
}

void output(int * elite, int machine, int job, int all_operation)
{
	FILE * fp;
	fp = fopen("output.txt", "w");

	Result result[MAX_MATRIX][MAX_MATRIX];
	int i, j;
	for (i = 0; i <= machine; i++)
		for (j = 0; j <= job; j++) {
			Result temp = { -1, -1, -1, -1 };
			result[i][j] = temp;
		}
	int machineEndTime[Max_Length];
	int jobEndTime[Max_Length];
	int index[Max_Length];
	memset(machineEndTime, 0, Max_Length);
	memset(jobEndTime, 0, Max_Length);
	memset(index, 0, Max_Length);
	int jobNum;
	int operationNum;
	int machineNum;
	int begin;
	int end;
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
		while (result[machineNum][j].begin != -1)
			j++;
		result[machineNum][j].begin = begin;
		result[machineNum][j].end = end;
		result[machineNum][j].job = jobNum;
		result[machineNum][j].operation = operationNum;
	}
	for (i = 1; i <= machine; i++) {
		if (result[i][0].begin == -1)
			continue;
		printf("M%d", i);
		fprintf(fp, "M%d", i);
		for (j = 0; j < job; j++) {
			if (result[i][j].begin == -1)
				break;
			printf(" (%d,%d-%d,%d)", result[i][j].begin, result[i][j].job, result[i][j].operation, result[i][j].end);
			fprintf(fp, " (%d,%d-%d,%d)", result[i][j].begin, result[i][j].job, result[i][j].operation, result[i][j].end);
		}
		printf("\n");
		fprintf(fp, "\n");
	}
	printf("End %d\n", best_fitness);
	fprintf(fp, "End %d\n", best_fitness);
	fclose(fp);
}