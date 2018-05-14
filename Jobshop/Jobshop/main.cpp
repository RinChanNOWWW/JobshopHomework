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

int main(void)
{
	All_job job;
	input(&job);
	int i, j;
	int** Population;
	int all_operation;
    Population = newPopulation(job, &all_operation);
	printf("\n\n");
	for (i = 1; i <= ITRATE; i++) {
		Population = nextPopulation(Population, job.machine_amount, job.job_amount, all_operation);
		output(Population, job.machine_amount, job.job_amount, all_operation);
		printf("\n");
	}
	deletePopulation(Population);
	system("pause");
	return 0;
}