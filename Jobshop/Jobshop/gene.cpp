/**
 * def of gene.h
 *
 * gene.c
 * by Hzy
 * 2018-5-12
 */
#pragma once
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gene.h"

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
}

/* poputlation */
int** newPopulation(All_job require)
{
	int all_operation = 0;
	int i, j, k = 0;
	for (i = 0; i < require.job_amount; i++)
		all_operation += require.operation_amount[i];
	int* chromo = NULL;
	int** population = (int **)malloc(sizeof(int *) * POPULATION);
	for (i = 0; i < POPULATION; i++) {
		creatChromo(require, all_operation);
		random_shuffle(chromo, all_operation);
		population[i] = chromo;
	}
	return population;
}
void deletePopulation(int** population)
{
	int i, j;
	for (i = 0; i < POPULATION; i++)
		free(population[i]);
	free(population);
}
int** nextPopulation(int** oldpopulation, int machine, int job, int all_operation)
{
	int elite;
	elite = e_select(oldpopulation, machine, job, all_operation);
	int** nextPopulation;
	nextPopulation = (int**)malloc(sizeof(int*) * Max_Population);
	int i;
	for (i = 0; i < Max_Population; i++) {
		if (i == elite || i == roulette_select(oldpopulation, machine, job, all_operation))
			nextPopulation[i] = oldpopulation[i];
		else
			nextPopulation[i] = NULL;
	}

}
/* get Cmax */
int getIndex(int* chromo, int i)
{
	int k;
	int index = 0;
	for (k = 0; k <= i; k++)
		if (chromo[k] == chromo[i])
			index++;
	return index;
}
int getCmax(int* chromo, int machine, int job, int all_operation)
{
	int machineEndTime[Max_Length];
	int jobEndTime[MAX_LEN];

	int i, j;
	int machine_num;
	int used_time;
	int index;
	int maxTime;
	int cMax = 0;
	for (i = 0; i < machine; i++) // initialize
		machineEndTime[i] = 0;
	for (i = 0; i < job; i++)
		jobEndTime[i] = 0;
	for (i = 0; i < all_operation; i++) {
		index = getIndex(chromo, i);
		machine_num = MachineNum[chromo[i]][index];
		used_time = Time[chromo[i]][index];
		maxTime = used_time + getMax(machineEndTime[machine_num - 1], jobEndTime[chromo[i] - 1]);
		machineEndTime[machine_num - 1] = maxTime;
		jobEndTime[chromo[i] - 1] = maxTime;
	}
	for (i = 0; i < machine; i++)
		if (machineEndTime[i] > cMax)
			cMax = machineEndTime[i];
	return cMax;
}

/* crossover */
int* order_crossover(int* p1, int* p2, int all_operation, int n)
{
	int* child1 = NULL;
	int* child2 = NULL;
	int* temp1 = NULL;
	int* temp2 = NULL;
	int* index1 = NULL;
	int* index2 = NULL;
	child1 = (int *)malloc(sizeof(int) * all_operation);
	child2 = (int *)malloc(sizeof(int) * all_operation);
	temp1 = (int *)malloc(sizeof(int) * all_operation);
	temp2 = (int *)malloc(sizeof(int) * all_operation);
	int i, j, k;
	int t;
	srand(clock());
	i = rand() % all_operation;
	j = rand() % all_operation;
	while (i == j)
		j = rand() % all_operation;
	if (i > j) {
		t = i;
		i = j;
		j = t;
	}
	index1 = (int *)malloc(sizeof(int) * (j - i + 1));
	index2 = (int *)malloc(sizeof(int) * (j - i + 1));
	for (k = 0; k < j - i + 1; k++) {
		index1[k] = getIndex(p1, i + k);
		index2[k] = getIndex(p2, i + k);
	}
	for (k = i; k <= j; k++) {
		child1[k] = p1[k];
		child2[k] = p2[k];
	}
	int s = 0;
	for (k = j + 1; k <= i - 1; k++) {
		if (k >= all_operation)
			k = 0;
		temp1[s] = p1[k];
		temp2[s] = p2[k];
		s++;
	}
	int n;
	for (k = 0; k < all_operation; k++) 
		for (n = 0; n < j - i + 1; n++) {
			if (temp1[k] == child1[n + i] && getIndex(temp1, k))
				temp1[k] = 0;
			if (temp2[k] == child2[n + i] && getIndex(temp2, k))
				temp2[k] = 0;
		}
	int s1 = 0;
	int s2 = 0;
	for (k = j + 1; k <= i - 1; k++) {
		if (k > all_operation)
			k = 0;
		if (temp1[s1] == 0)
			s1++;
		else {
			child1[k] = temp1[s1];
			s1++;
		}
		if (temp2[s2] == 0)
			s2++;
		else {
			child2[k] = temp2[s2];
			s2++;
		}
	}
	free(index1); free(index2); free(temp1); free(temp2); 
	temp1 = NULL; temp2 = NULL; index1 = NULL;index2 = NULL;
	if (n == 1)
		return child1;
	return child2;
}

/* mutation */
void mutation(int* chromo, int all_operation)
{
	int i, j;
	srand(clock());
	i = rand() % all_operation;
	j = rand() % all_operation;
	exchange(&chromo[i], &chromo[j]);
}

/* select */
int e_select(int** population, int machine, int job, int all_operation)
{
	int i;
	int elite;
	int best_fitness = getCmax(population[0], machine, job, all_operation);
	int fitness;
	for (i = 0; i < Max_Population; i++) {
		fitness = getCmax(population[i], machine, job, all_operation);
		if (fitness < best_fitness) {
			best_fitness = fitness;
			elite = i;
		}
	}
	return elite;
}
int roulette_select(int** population, int machine, int job, int all_operation)
{
	int* Cmax = (int*)malloc(sizeof(int) * Max_Population);
	double* P = (double*)malloc(sizeof(double) * Max_Population);
	memset(P, 0, sizeof(P));
	int i;
	int Cmax_sum = 0;
	for (i = 0; i < Max_Population; i++) {
		Cmax[i] = getCmax(population[i], machine, job, all_operation);
		Cmax_sum += Cmax[i];
	}
	P[0] = ((double)(Cmax_sum - Cmax[0])) / Cmax_sum;
	for (i = 1; i < Max_Population; i++) {
		P[i] = P[i - 1] + (double)(Cmax_sum - Cmax[i]) / Cmax_sum;
	}
	free(Cmax);
	srand(clock());
	double r;
	r = ((double)(rand() % 10000)) / 10000;
	if (r < P[0]) {
		free(P);
		return 0;
	}
	else {
		for (i = 1; i < Max_Population; i++) {
			if (r > P[i - 1] && r < P[i]) {
				free(P);
				return i;
			}
		}
	}
}