#ifndef _BASE_H_
#define _BASE_H_


#define MAX_LEN 20
#define MAX_MATRIX 20

typedef struct {
	int machine_amount;
	int job_amount;
	int operation_amount[MAX_LEN];
} All_job;

int MachineNum[MAX_MATRIX][MAX_MATRIX];
int Time[MAX_MATRIX][MAX_MATRIX];
#endif // !_BASE_H_
