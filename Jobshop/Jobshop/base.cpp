/**
 * def of base.h
 *
 * base.c
 * by Hzy
 * 2018-5-10
 */
#include <time.h>
#include <stdlib.h>
#include "base.h"
#include "gene.h"
extern int best_fitness;

void exchange(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int getMax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

void random_shuffle(int* a, int n)
{
	int index, i;
	for (i = 0; i < n; i++) {
		index = rand() % (n - i) + i;
		if (index != i) {
			exchange(&a[i], &a[index]);
		}
	}
}

void arrayCopy(int * destination, int * source, int n)
{
	int i;
	for (i = 0; i < n; i++)
		destination[i] = source[i];
}