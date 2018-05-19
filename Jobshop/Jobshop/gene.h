/**
 * base of GA
 * 
 * gene.h
 * by Hzy
 * 2018-5-10
 */
#pragma once
#ifndef _GENE_H_
#define _GENE_H_

#include "base.h"

#define Max_Length 300 // contemp
#define Max_Population 300 // contempss
#define Px 0.95
#define Pm 0.25
#define ITRATE 1500

/* chromosome */
int * creatChromo(All_job require, int all_operation);
/* population */
int** newPopulation(All_job require, int* all_operation);
void deletePopulation(int** population);
int** nextPopulation(int** oldpopulation, int machine, int job, int all_operation);
/* get Cmax */
int getCmax(int* chromo, int all_operation);
/* crossover */
void order_crossover(int* p1, int* p2, int all_operation);

/* mutation */
void mutation(int* chromo, int all_operation);

/* select */
int e_select(int** population, int all_operation);
double* roulette(int** population, int all_operation);
#endif // !_GENE_H_
