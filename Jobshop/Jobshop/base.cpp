/**
 * def of base.h
 *
 * base.c
 * by ������
 * 2018-5-10
 */

#include <time.h>
#include <stdlib.h>
#include "base.h"
#include "gene.h"

extern int best_fitness;              //���Ž�

/**
 * ����������
 * 
 * a ����������
 * b ��һ������������
 */
void exchange(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * �������������ֵ
 *
 * a һ����
 * b ��һ����
 * return a��b�еĽϴ�ֵ
 */
int getMax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

/**
 * �������һ������
 *
 * a[] ��Ҫ�����ҵ�����
 * n ��������Ч���ݵĸ���
 */
void random_shuffle(int* a, int n)
{
	int index, i;
	for (i = 0; i < n; i++) {
		index = rand() % (n - i) + i;          //���������������λ��
		if (index != i) {
			exchange(&a[i], &a[index]);
		}
	}
}

/**
 * ��һ���������鸴�Ƶ���һ������������
 *
 * destination[] ���Ʋ���������
 * source[] �����Ƶ�����
 * n ����Ĺ�ģ
 */
void arrayCopy(int * destination, int * source, int n)
{
	int i;
	for (i = 0; i < n; i++)
		destination[i] = source[i];
}