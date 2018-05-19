/**
 * main
 *
 * main.c
 *
 * 2018-5-14
 */
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "file.h"
#include "gene.h"

extern int MachineNum[MAX_MATRIX][MAX_MATRIX];
extern int Time[MAX_MATRIX][MAX_MATRIX];
extern int best_fitness;
extern int elite;

int main(void)
{
	srand(clock());
	clock_t start, end;
	double t;
	All_job job;
	//input(&job);
	read_from_file(&job);
	start = clock();
	int i;
	int** Population;
	int all_operation;
    Population = newPopulation(job, &all_operation);
	for (i = 1; i <= ITRATE; i++) {
		Population = nextPopulation(Population, job.machine_amount, job.job_amount, all_operation);
		//printf("%d\n", best_fitness);
	}
	printf("结果输出如下:\n");
	output(Population[elite], job.machine_amount, job.job_amount, all_operation);
	deletePopulation(Population);
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%lf", t);
	system("pause");
	return 0;
}