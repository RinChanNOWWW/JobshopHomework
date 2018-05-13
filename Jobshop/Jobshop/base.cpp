/**
 *
 *
 *
 */
#include <time.h>
#include <stdlib.h>
#include "base.h"
#include "gene.h"

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
	srand(clock());
	for (i = 0; i < n; i++) {
		index = rand() % (n - i) + i;
		if (index != i) {
			exchange(&a[i], &a[index]);
		}
	}
}