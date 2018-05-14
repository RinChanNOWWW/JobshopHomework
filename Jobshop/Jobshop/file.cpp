/**
 * def of file.h
 *
 * file.c
 * by Hzy
 * 2018-5-14
 */
#pragma once
#include<stdio.h>
#include "file.h"
#include "gene.h"

int MachineNum[MAX_MATRIX][MAX_MATRIX];
int Time[MAX_MATRIX][MAX_MATRIX];

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

int output(int ** population, int machine, int job, int all_operation)
{
	int elite;
	elite = e_select(population, machine, job, all_operation);
	int ans;
	ans = getCmax(population[elite], machine, job, all_operation);
	return ans;
}