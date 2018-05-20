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

/* ��file.cpp */
extern int MachineNum[MAX_MATRIX][MAX_MATRIX];
extern int Time[MAX_MATRIX][MAX_MATRIX];
/* ��gene.cpp */
extern int best_fitness;
extern int elite;

int main(void)
{
	srand(clock());             //����һ�������ʱ�䣨����Ϊ��λ�������������������
	/* ������������������Ҫ��ʱ�� */
	clock_t start, end;         
	double t;         

	All_job job;      //��¼���������
	start = clock();
	read_from_file(&job);
	int i;
	int** Population;
	int all_operation;
	/* ��ʼ����Ⱥ */
    Population = newPopulation(job, &all_operation);
	/* ������������ */
	for (i = 1; i <= ITERATE; i++) 
		Population = nextPopulation(Population, job.machine_amount, job.job_amount, all_operation);
	/* ��������� */
	printf("����������:\n");
	output(Population[elite], job.machine_amount, job.job_amount, all_operation);
	deletePopulation(Population);
	/* �����������ʱ�� */
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%lf", t);
	system("pause");
	return 0;
}