/**
 * def of gene.h
 *
 * gene.c
 * by Hzy
 * 2018-5-12
 */
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gene.h"

extern int MachineNum[MAX_MATRIX][MAX_MATRIX];
extern int Time[MAX_MATRIX][MAX_MATRIX];
int Cmax[Max_Length];
int Cmax_sum;
int best_fitness = INT_MAX;
int elite;

/* chromosome */
int * creatChromo(All_job require, int all_operation)
{
	int* chromo = (int *)malloc(sizeof(int) * all_operation);
	int i, j, k = 0;
	for (i = 0; i < require.job_amount; i++)
		for (j = 0; j < require.operation_amount[i]; j++) {
			chromo[k] = i + 1;
			k++;
		}
	return chromo;
}

/* poputlation */
int** newPopulation(All_job require, int* all_operation)
{
	*all_operation = 0;
	int i, k = 0;
	for (i = 0; i < require.job_amount; i++)
		*all_operation += require.operation_amount[i];
	int* chromo = NULL;
	int** population = (int **)malloc(sizeof(int *) * Max_Population);
	for (i = 0; i < Max_Population; i++) {
		chromo = creatChromo(require, *all_operation);
		random_shuffle(chromo, *all_operation);
		population[i] = chromo;
	}
	return population;
}
void deletePopulation(int** population)
{
	int i;
	for (i = 0; i < Max_Population; i++)
		free(population[i]);
	free(population);
}
int** nextPopulation(int** oldpopulation, int machine, int job, int all_operation)
{
	memset(Cmax, 0, Max_Population);
	int i, j;
	best_fitness = 0x3f3f3f3f;
	/* next population*/
	int** nextPopulation;
	nextPopulation = (int**)malloc(sizeof(int*) * Max_Population);
	for (i = 0; i < Max_Population; i++)
		nextPopulation[i] = (int *)malloc(sizeof(int) * all_operation);
	/* select elite */
	Cmax_sum = 0;
	int runtime;
	//elite = e_select(oldpopulation, all_operation);
	for (i = 0; i < Max_Population; i++) {
		Cmax[i] = getCmax(oldpopulation[i], all_operation);
		Cmax_sum += Cmax[i];
		if (Cmax[i] < best_fitness) {
			best_fitness = Cmax[i];
			elite = i;
		}
	}
	arrayCopy(nextPopulation[0], oldpopulation[elite], all_operation);
	/* roulette */
	double * P = roulette(oldpopulation, all_operation);
	double pick;
	for (i = 1; i < Max_Population; i++) {
		int flag = 0;
		pick = ((double)rand()) / RAND_MAX;
		for (j = 0; j < Max_Population; j++) {
			if (pick < P[j]) {
				arrayCopy(nextPopulation[i], oldpopulation[j], all_operation);
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			arrayCopy(nextPopulation[i], oldpopulation[elite], all_operation);
	}
	free(P);
	double p;
	for (i = 1; i < Max_Population - 1; i = i + 2) {
		p = ((double)rand()) / RAND_MAX;
		if (p < Px) {
			order_crossover(nextPopulation[i], nextPopulation[i + 1], all_operation);
		}
			
	}
	for (i = 1; i < Max_Population; i++) {
		p = ((double)rand()) / RAND_MAX;
		if (p < Pm)
			mutation(nextPopulation[i], all_operation);
	}
	deletePopulation(oldpopulation);
	return nextPopulation;
}
int getCmax(int* chromo, int all_operation)
{
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
		begin = machineEndTime[machineNum] > jobEndTime[jobNum] ? machineEndTime[machineNum] : jobEndTime[jobNum];
		end = begin + Time[jobNum][operationNum];
		machineEndTime[machineNum] = end;
		jobEndTime[jobNum] = end;
		if (Cmax < end)
			Cmax = end;
	}
	return Cmax;
}

/* crossover */
void order_crossover(int* p1, int* p2, int all_operation)
{
	
	int i, j, k;
	int* child1 = NULL;
	int* child2 = NULL;
	child1 = (int *)malloc(sizeof(int) * all_operation);
	child2 = (int *)malloc(sizeof(int) * all_operation);
	i = rand() % all_operation;
	j = rand() % all_operation;
	int head1 = 0;
	int head2 = 0;
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
	free(child1); free(child2); 

}

/* mutation */
void mutation(int* chromo, int all_operation)
{
	int i, j;
	i = rand() % all_operation;
	j = rand() % all_operation;
	exchange(&chromo[i], &chromo[j]);
}

/* select */
int e_select(int** population, int all_operation)
{
	int i;
	int elite = 0;
	int fitness;
	for (i = 0; i < Max_Population; i++) {
		fitness = getCmax(population[i], all_operation);
		if (fitness < best_fitness) {
			best_fitness = fitness;
			elite = i;
		}
	}
	return elite;
}
double* roulette(int** population, int all_operation)
{
	double* P = (double*)malloc(sizeof(double) * Max_Population);
	memset(P, 0, sizeof(P));
	int i;
	int Cmax_sum_differ;
	Cmax_sum_differ = (Max_Population - 1) * Cmax_sum;
	P[0] = ((double)(Cmax_sum - Cmax[0])) / Cmax_sum_differ;
	for (i = 1; i < Max_Population; i++) {
		P[i] = P[i - 1] + ((double)(Cmax_sum - Cmax[i])) / Cmax_sum_differ;
	}

	return P;
}