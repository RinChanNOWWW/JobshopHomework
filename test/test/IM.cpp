/**
 * IM.c
 *
 * OM.h的实现部分
 * By Hzy
 * 2018-5-6
 */

#include "IM.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * 初始化模块
 *
 */
void input()
{
	scanf("%d %d", &J_amount, &M_amount);
	int i, j;
	int job_t = 0;
	int number = 1;         //工序序号
	for (i = 1; i <= J_amount; i++)
		scanf("%d", &OA[i]);
	for (i = 1; i <= J_amount; i++)
		for (j = 1; j <= OA[i]; j++)
			JO[i][j] = number++;
	for (i = 1; i <= J_amount; i++) {
		for (j = 1; j <= OA[i]; j++) {
			scanf("%d %d", &PT[i][j], &OM[i][j]);
			job_t += PT[i][j];
		}
		if (job_t > max_job_t) {
			max_job_t = job_t;
			max_job_t = i;
		}
		job_t = 0;
	}
}
void time_calculate(machine* MO[MAX])
{

}

void initial(int J_amount, int M_amount)
{
	machine* head_operation = NULL;
	machine* cur_operation = NULL;
	machine* last_operation = NULL;
	int i = 1;
	int j, k;
	while (i <= M_amount) {
		for (j = 1; j <= MAX; j++) {
			if (JO[max_job_t][j] == 0)
				break;
			else if (OM[max_job_t][j] == i) {
				cur_operation = (machine*)malloc(sizeof(machine));
				cur_operation->operation = JO[max_job_t][j];
				if (head_operation == NULL) {
					head_operation = cur_operation;
					last_operation = cur_operation;
				}
				else {
					last_operation->next_operation = cur_operation;
					last_operation = cur_operation;
				}
			}
		}
		last_operation->next_operation = NULL;
		head_operation = NULL;
		MO[i] = head_operation;
		i++;
	}
}

void delete_MO(machine* MO[MAX], int M_amount)
{
	int i;
	machine* cur_operation = NULL;
	for (i = 1; i <= M_amount; i++) {
		while (MO[i] != NULL) {
			cur_operation = MO[i];
			MO[i] = MO[i]->next_operation;
			free(cur_operation);
		}
	}
}
