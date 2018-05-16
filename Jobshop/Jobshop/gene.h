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

#define Max_Length 100 // contemp
#define Max_Population 100 // contempss
#define Px 0.95
#define Pm 0.05
#define ITRATE 2000

/* chromosome */
int * creatChromo(All_job require, int all_operation);
/* population */
int** newPopulation(All_job require, int* all_operation);
void deletePopulation(int** population);
int** nextPopulation(int** oldpopulation, int machine, int job, int all_operation);
/* get Cmax */
int getCmax(int* chromo, int machine, int job, int all_operation);
int getIndex(int* chromo, int i);
/* crossover */
void order_crossover(int* p1, int* p2, int all_operation);

/* mutation */
void mutation(int* chromo, int all_operation);

/* select */
int e_select(int** population, int machine, int job, int all_operation);
int roulette_select(int** population, int machine, int job, int all_operation);
#endif // !_GENE_H_
