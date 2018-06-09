/**
 * def of file.h
 *
 * file.c
 * by ������
 * 2018-5-14
 */
#pragma once

#include<stdio.h>
#include <string.h>
#include <time.h>
#include "file.h"
#include "gene.h"

int MachineNum[MAX_MATRIX][MAX_MATRIX];       //����i��j������ӹ����õĻ�����
int Time[MAX_MATRIX][MAX_MATRIX];             //����i��j������ӹ�����ʱ��
extern int best_fitness;                      //���Ž�
extern clock_t start, end;

/**  û�а�Ҫ���������ʱ�������뺯��
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
*/

/**
 * ���ļ�����ѡ�Ӽ���/stdin���ж�ȡ��Ҫ������
 *
 * job �洢���л������ݵĽṹ������
 */
void read_from_file(All_job * job)
{
//	int opt;                            //ѡ������
	FILE * fp;        
	/* �����ļ��������� */
	fp = fopen("input.txt", "r");
//	printf("���ļ�/�������룿\n");
//	printf("����1���ļ����룬2�Ӽ�������:\n");
/*	scanf("%d", &opt);
	if (opt == 2) {
		fp = stdin;                     //��ѡ��Ӽ������룬���ļ���������Ϊ��׼������stdin
		printf("����������:\n");
	}*/
	/* ��ȡ���ݲ��� */
	fscanf(fp, "%d %d", &(*job).job_amount, &(*job).machine_amount);     
/*	int count = 0;
	int jobNum;
	while ((fscanf(fp, "%d", &jobNum) == 1) && jobNum != -1) {
		count = 0;                           //��¼�˹���һ���м�������
		int operation = 1;                   //��¼�˹���Ϊ�����ĵڼ�������
		char ch;*/
		/* ����ÿ���������� */
/*		while ((ch = fgetc(fp)) != '\n') {
			if (ch == ' ')                   //���Կո�
				continue;
			else if (ch == ')')              //�������� 
				continue;
			else if (ch == '(') {            //��������
				count++;
				fscanf(fp, "%d", &Time[jobNum][operation]);
				fgetc(fp);
				fscanf(fp, "%d", &MachineNum[jobNum][operation]) ;
				operation++;
			}
		}
		(*job).operation_amount[jobNum - 1] = count;
	}*/
	int i, j;
	int M, T;
	for (i = 1; i <= job->job_amount; i++) {
		for (j = 1; j <= job->machine_amount; j++) {
			fscanf(fp, "%d %d", &M, &T);
			MachineNum[i][j] = M + 1;
			Time[i][j] = T;
		}
		job->operation_amount[i - 1] = job->machine_amount;
	}
	/* �ر��ļ� */
	fclose(fp);
}

/**
 * ���������
 *
 * elite[] ���Ž�����Ӧ�ı���Ⱦɫ��
 * machine �ܻ�����
 * job �ܹ�����
 * all_operation �ܹ�����
 */
void output(int * elite, int machine, int job, int all_operation)
{
	/* �����ļ����� */
	FILE * fp;
	fp = fopen("output.txt", "w");
	/* ����һ����¼���������Ϣ�Ķ�ά���� */
	Result result[MAX_MATRIX][MAX_MATRIX];         //����i�ϵ�j������
	/* ��ʼ��������� */
	int i, j;
	for (i = 0; i <= machine; i++)
		for (j = 0; j <= job; j++) {
			Result temp = { -1, -1, -1, -1 };
			result[i][j] = temp;
		}
	/* �������ṹ������Ҫ������ */
	int machineEndTime[Max_Length];                //����i���������¹����ʱ��
	int jobEndTime[Max_Length];                    //����i�������¹����ʱ�� 
	int index[Max_Length];                         //���¹����ڹ����е����
	/* ��ʼ������ */
	memset(machineEndTime, 0, Max_Length);
	memset(jobEndTime, 0, Max_Length);
	memset(index, 0, Max_Length);
	/* ��������Ҫ�ı��� */
	int jobNum;                                    //�ù������ڹ�����
	int operationNum;                              //�ù����ǹ����ĵڼ�������
	int machineNum;                                //�ù������ڻ�����
	int begin;                                     //�ù���Ŀ�ʼʱ��
	int end;                                       //�ù���Ľ���ʱ��
	/* ��˳���������Ⱦɫ�壬�𹤼����� */
	for (i = 0; i < all_operation; i++) {
		jobNum = elite[i];
		index[jobNum]++;
		operationNum = index[elite[i]];
		machineNum = MachineNum[jobNum][operationNum];
		begin = machineEndTime[machineNum] > jobEndTime[jobNum] ? machineEndTime[machineNum] : jobEndTime[jobNum];
		end = begin + Time[jobNum][operationNum];
		machineEndTime[machineNum] = end;
		jobEndTime[jobNum] = end;
		j = 0;
		/* ��˳���ҵ��û����Ľ��������û�����ݵ�λ�� */
		while (result[machineNum][j].begin != -1)
			j++;
		/* ������ */
		result[machineNum][j].begin = begin;
		result[machineNum][j].end = end;
		result[machineNum][j].job = jobNum;
		result[machineNum][j].operation = operationNum;
	}
	/* ��ӡ��� */
	for (i = 0; i <= machine; i++) {     //����ÿ�������Ľ������
		/* �������ݵ�λ�ÿ�ʼ */
		if (result[i][0].begin == -1)
			continue;
		printf("M%d", i - 1);               //����Ļ
		fprintf(fp, "M%d", i - 1);          //���ļ�
		/* ���ж�ȡ */
		for (j = 0; j < job; j++) {
			if (result[i][j].begin == -1)     //��û�����ݵ�λ�ý���
				break;
			printf(" (%d,%d-%d,%d)", result[i][j].begin, result[i][j].job - 1, result[i][j].operation - 1, result[i][j].end);
			fprintf(fp, " (%d,%d-%d,%d)", result[i][j].begin, result[i][j].job - 1, result[i][j].operation - 1, result[i][j].end);
		}
		printf("\n");
		fprintf(fp, "\n");
	}
	printf("End %d\n", best_fitness);
	fprintf(fp, "End %d\n", best_fitness);
	fprintf(fp, "Time used:%.3lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	fclose(fp);
}