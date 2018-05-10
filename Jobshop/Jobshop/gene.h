/**
 * gene.h
 * 
 * base of GA
 * by Hzy
 * 2018-5-10
 */

#ifndef _GENE_H_
#define _GENE_H_

#include "base.h"

#define Max_Length 20  // contemp
#define Max_Poputatoin 300  // contempss
 
/* chromosome */
int chromosome[Max_Length];
int* creatChromo(All_job require);

/* poputation */
int** InitiaPoputation();

/* get Cmax */
int getCmax(int* chromo);

/* select */





/* cross */


/* mutation */


#endif // !_GENE_H_
