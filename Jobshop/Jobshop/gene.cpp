/**
 * def of gene.h
 *
 * gene.c
 * by ������
 * 2018-5-12
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "gene.h"

extern int MachineNum[MAX_MATRIX][MAX_MATRIX];     //��file.cpp
extern int Time[MAX_MATRIX][MAX_MATRIX];           //��file.cpp
int Cmax[Max_Length];                              //һ����Ⱥÿ������ļӹ�ʱ��
long long Cmax_sum;                                      //�ܼӹ�ʱ��
int best_fitness = INT_MAX;                        //���Ž�
int elite;                                         //��Ӣ����λ��
int Cmax_max;
int elite_chromo[Max_Length];

/**
 * ����һ������Ⱦɫ��
 *
 * require ��ҵ����ṹ��
 * all_operation �ܹ�����
 * return ָ���Ⱦɫ���ָ��
 */
int * creatChromo(All_job require, int all_operation)
{
	/* ������������ݱ��� */
	int* chromo = (int *)malloc(sizeof(int) * all_operation);
	int i, j, k = 0;
	for (i = 0; i < require.job_amount; i++)
		for (j = 0; j < require.operation_amount[i]; j++) {
			chromo[k] = i + 1;
			k++;
		}
	return chromo;
}

/**
 * ��������ʼ��һ����Ⱥ
 *
 * require ��ҵ����ṹ��
 * all_operation ָ���ܹ�������ָ��
 * return ָ�����Ⱥ��ָ��
 */
int** newPopulation(All_job require, int* all_operation)
{
	*all_operation = 0;     //��ʼ������
	int i, k = 0;
	for (i = 0; i < require.job_amount; i++)
		*all_operation += require.operation_amount[i];
	int* chromo = NULL;
	int** population = (int **)malloc(sizeof(int *) * Max_Population);
	for (i = 0; i < Max_Population; i++) {
		chromo = creatChromo(require, *all_operation);     //����һ��Ⱦɫ��
		random_shuffle(chromo, *all_operation);            //����������Ⱦɫ��
		population[i] = chromo;                            //¼����Ⱥ
	}
	return population;
}

/**
 * ������Ⱥ
 *
 * population ָ��һ����Ⱥ��ָ��
 */
void deletePopulation(int** population)
{
	/* freeһ����ά���� */
	int i;
	for (i = 0; i < Max_Population; i++)
		free(population[i]);
	free(population);
}

/**
 * ������Ⱥ��������
 *
 * oldpopulation ָ������Ⱥ����������ָ��
 * machine �ܻ�����
 * job �ܹ�����
 * all_operation �ܹ�����
 * return ָ������Ⱥ���Ӵ�����ָ��
 */
int** nextPopulation(int** oldpopulation, int machine, int job, int all_operation)
{
	memset(Cmax, 0, Max_Population); //��ʼ������ 
	int i, j;
	/* ��̬��������Ⱥ�Ķ�λ���� */
	int** nextPopulation;
	nextPopulation = (int**)malloc(sizeof(int*) * Max_Population);
	for (i = 0; i < Max_Population; i++)
		nextPopulation[i] = (int *)malloc(sizeof(int) * all_operation);
	/* ���ɼӹ�ʱ�䣨��Ӧ�ȣ����� */
	Cmax_sum = 0;
	int runtime;
	for (i = 0; i < Max_Population; i++) {
		Cmax[i] = getCmax(oldpopulation[i], all_operation);
		Cmax_sum = Cmax_sum + Cmax[i];
		if (Cmax[i] < best_fitness) {        //ѡ����Ӣ
			best_fitness = Cmax[i];          //�������Ž�
			elite = i;
			arrayCopy(elite_chromo, oldpopulation[i], all_operation);
		}
		if (Cmax[i] > Cmax_max)
			Cmax_max = Cmax[i];
	}
	/* ������Ӣ */
	arrayCopy(nextPopulation[0], oldpopulation[elite], all_operation);
	/* �����ֶ��� */
	double * P = roulette(oldpopulation, all_operation);
	/* �����ֶ��̴�����Ⱥ��������ѡ���Ӵ�¼������Ⱥ���Ӵ��� */
	double pick;     //ѡ�����
	for (i = 1; i < Max_Population; i++) {     //��Ӣ��������
		int flag = 0;
		pick = ((double)rand()) / RAND_MAX;    //������ɸ���
		for (j = 0; j < Max_Population; j++) {
			if (pick < P[j]) {
				arrayCopy(nextPopulation[i], oldpopulation[j], all_operation);
				flag = 1;
				break;
			}
		}
		if (flag == 0)    //�������©��¼�뾫Ӣ
			arrayCopy(nextPopulation[i], oldpopulation[elite], all_operation);
	}
	/* �����ֶ��� */
	free(P);
	/* �����ʽ��� */
	double p;
	int choice, cnt = 0;
	for (i = 1; i < Max_Population ; i = i + 1) {
		p = ((double)rand()) / RAND_MAX;       //������ɽ������
		if (p < Px) {   /* ǰ���������� */
			cnt++;
			if (cnt % 2 == 0)
				order_crossover(nextPopulation[i], nextPopulation[choice], all_operation);
			else
				choice = i;
		}
			
	}
	/* �����ʱ��� */
	for (i = 1; i < Max_Population; i++) {
		p = ((double)rand()) / RAND_MAX;
		if (p < Pm)
			mutation(nextPopulation[i], all_operation);
	}
	/* ��������Ⱥ�������� */
	deletePopulation(oldpopulation);
	/* ��������Ⱥ���Ӵ��� */
	return nextPopulation;
}

/**
 * ����˱���Ⱦɫ���Ӧ�ļӹ�ʱ��
 *
 * chromo[] ����Ⱦɫ��
 * all_operation �ܹ�����
 * return �ӹ�ʱ��
 */
int getCmax(int* chromo, int all_operation)
{
	/* ͬfile.cpp�к���output_to_file�еĳ�ʼ������� */
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
		/* �ҳ���������ʱ��͹�������ʱ������ֵ */
		begin = machineEndTime[machineNum] > jobEndTime[jobNum] ? machineEndTime[machineNum] : jobEndTime[jobNum];
		end = begin + Time[jobNum][operationNum];
		/* ���� */
		machineEndTime[machineNum] = end;
		jobEndTime[jobNum] = end;
		if (Cmax < end)
			Cmax = end;
	}
	return Cmax;
}

/**
 * Ⱦɫ�彻�棨�Ľ��棩
 *
 * p1 ����1Ⱦɫ��
 * p2 ����2Ⱦɫ��
 * all_operation �ܹ�����
 */
void order_crossover(int* p1, int* p2, int all_operation)
{
	
	int i, j, k;
	int* child1 = NULL;
	int* child2 = NULL;
	child1 = (int *)malloc(sizeof(int) * all_operation);
	child2 = (int *)malloc(sizeof(int) * all_operation);
	i = rand() % all_operation;  //�����������λ��
	j = rand() % all_operation;  //�����������λ��
	int head1 = 0;
	int head2 = 0;
	/* ���棨α�� */
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
	/* �ͷ��ڴ� */
	free(child1); free(child2); 

}

/**
 * Ⱦɫ�����
 *
 * chromo[] Ҫ����ı���Ⱦɫ��
 * all_operation �ܹ�����
 */
void mutation(int* chromo, int all_operation)
{
	int i, j;
	/* �����������λ�� */
	i = rand() % all_operation;   
	j = rand() % all_operation;
	while (i == j || chromo[i] == chromo[j]) {
		i = rand() % all_operation;
	}
	/* �������������λ�õı������������� */
	exchange(&chromo[i], &chromo[j]);
}

/**
 * ����һ���ֶ���
 *
 * population ��Ⱥ
 * all_operation �ܹ�����
 * return �ֶ���-һ����������
 */
double* roulette(int** population, int all_operation)
{
	/**
	 * ��Ϊ�ӹ�ʱ��Խ����Ӧ��Խ��
	 * ������һ���ӹ�ʱ�䵽��Ӧ�ȵ�ӳ������ֶ���
	 * ���ܼӹ�ʱ���뵥������ӹ�ʱ��Ĳ���Ϊ�ֶ���Ԫ��
	 * �����������ÿ����Ӧ�ĸ���
	 */
	double* P = (double*)malloc(sizeof(double) * Max_Population);
	/* ��ʼ�� */
	memset(P, 0, sizeof(P));
	int ave;
	int i;
	int temp;
	int fitness[Max_Length] = { 0 };
	int fit_sum = 0;
	ave = Cmax_sum / Max_Population;
	temp = -1 * (ave - Cmax_max) + ave / 10;
	
	for (i = 0; i < Max_Population; i++) {
		fitness[i] = ave - Cmax[i] + temp;
//		fitness[i] = exp((double)Cmax[i]);
		fit_sum += fitness[i];
	}
	double recordfit[Max_Length] = { 0 };
	for (i = 0; i < Max_Population; i++) {
		recordfit[i] = (double)fitness[i] / fit_sum;
		if (i == 0)
			P[i] = recordfit[i];
		else
			P[i] = P[i - 1] + recordfit[i];
	}
	
	//int Cmax_sum_differ;     //�ܵĲ� 
	//Cmax_sum_differ = (Max_Population - 1) * Cmax_sum;
	//P[0] = ((double)(Cmax_sum - Cmax[0])) / Cmax_sum_differ;
	for (i = 0; i < Max_Population; i++) {
	//	P[i] = P[i - 1] + ((double)(Cmax_sum - Cmax[i])) / Cmax_sum_differ;
	}

	return P;
}