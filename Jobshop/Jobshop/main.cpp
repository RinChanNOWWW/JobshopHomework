/**
 * main
 *
 * main.c
 *
 * by ��ϣ֮
 * 2018-5-14
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "file.h"
#include "gene.h"

/* ��file.cpp */
extern int MachineNum[MAX_MATRIX][MAX_MATRIX];
extern int Time[MAX_MATRIX][MAX_MATRIX];
/* ��gene.cpp */
extern int best_fitness;
extern int elite;
extern int elite_chromo[Max_Length];
clock_t start, end;

int main(void)
{
	srand(time(NULL)); 

	//srand(clock());//����һ�������ʱ�䣨����Ϊ��λ�������������������
	/* ������������������Ҫ��ʱ�� */
	       
	double t;         

	All_job job;      //��¼���������
	read_from_file(&job);
	int i;
	int** Population;
	int all_operation = 0;
	int j;
	start = clock();
	for (j = 1; j <= 20; j++) {
		/* ��ʼ����Ⱥ */
		Population = newPopulation(job, &all_operation);
		/* ������������ */

		for (i = 1; i <= ITERATE; i++) {
			Population = nextPopulation(Population, job.machine_amount, job.job_amount, all_operation);
			//printf("%d\n", best_fitness);
		}
		/* ��������� */
		//printf("%d\n", best_fitness);
		deletePopulation(Population);
	}
	output(elite_chromo, job.machine_amount, job.job_amount, all_operation);
	/* �����������ʱ�� */
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Time Used:%.3lfs\n", t);
	system("pause");
	return 0;
}