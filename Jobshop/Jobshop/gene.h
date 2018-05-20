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

#define Max_Length 300            //����Ⱦɫ�����󳤶�
#define Max_Population 300        //�����Ⱥ����
#define Px 0.95                   //Ⱦɫ�彻�����
#define Pm 0.25                   //Ⱦɫ��������
#define ITERATE 1500              //��Ⱥ����������������

/**
 * ����һ������Ⱦɫ��
 *
 * require ��ҵ����ṹ��
 * all_operation �ܹ�����
 * return ָ���Ⱦɫ���ָ��
 */
int * creatChromo(All_job require, int all_operation);

/**
 * ��������ʼ��һ����Ⱥ
 * 
 * require ��ҵ����ṹ��
 * all_operation ָ���ܹ�������ָ��
 * return ָ�����Ⱥ��ָ��
 */
int** newPopulation(All_job require, int* all_operation);

/**
 * ������Ⱥ
 * 
 * population ָ��һ����Ⱥ��ָ��
 */
void deletePopulation(int** population);

/**
 * ������Ⱥ��������
 *
 * oldpopulation ָ������Ⱥ����������ָ��
 * machine �ܻ�����
 * job �ܹ�����
 * all_operation �ܹ�����
 * return ָ������Ⱥ���Ӵ�����ָ��
 */
int** nextPopulation(int** oldpopulation, int machine, int job, int all_operation);

/**
 * ����˱���Ⱦɫ���Ӧ�ļӹ�ʱ��
 *
 * chromo[] ����Ⱦɫ��
 * all_operation �ܹ�����
 * return �ӹ�ʱ��
 */
int getCmax(int* chromo, int all_operation);

/**
 * Ⱦɫ�彻�棨�Ľ��棩
 *
 * p1 ����1Ⱦɫ��
 * p2 ����2Ⱦɫ��
 * all_operation �ܹ�����
 */
void order_crossover(int* p1, int* p2, int all_operation);

/**
 * Ⱦɫ�����
 *
 * chromo[] Ҫ����ı���Ⱦɫ��
 * all_operation �ܹ�����
 */
void mutation(int* chromo, int all_operation);

/**
 * ����һ���ֶ���
 * 
 * population ��Ⱥ
 * all_operation �ܹ�����
 * return �ֶ���-һ����������
 */
double* roulette(int** population, int all_operation);

#endif // !_GENE_H_
