/**
 * IM.h
 *
 * ����ģ��
 * By Hzy
 * 2018-5-6
 */

#ifndef _IM_H_
#define _IM_H_

#define MAX 10           //���Ҷ���һ���������󳤶�
int J_amount, M_amount;  //�����������
int max_job_t;           //�ӹ�ʱ����������ܼӹ�ʱ��
int max_t_job;           //��ʱ��Ĺ���

/**
 * ��ʼ��ģ��
 *
 * ��˳���Է�����Ȼ����ʾ����0��������
 */
int JO[MAX][MAX];       //����-�������JO(ij)��ʾ����i�ĵ�j������
int OA[MAX];            //���������蹤����
int PT[MAX][MAX];       //�����ʱ���󣬶�ӦJO�и�������Ҫ��ʱ��
int OM[MAX][MAX];       //����-�������󣬶�ӦJO���������ڵĻ���
int ST[MAX][MAX];       //��ʼʱ����󣬶�ӦMO�и�����Ŀ�ʼʱ�䣬��0��ʼ
int ET[MAX][MAX];       //��ֹʱ����󣬶�ӦMO�и��������ֹʱ��

/* һ�������Ϲ������˳����������� */
typedef struct MACHINE {
	int operation;           //��������
	machine* next_operation;  //ָ����һ������
} machine;

machine* MO[MAX];         //ÿ�������ϵĹ���˳����һ���������飬Ԫ��Ϊ�����ͷ�ڵ�

/**
 * �ݶ������뺯��
 *
 */
void input();

/**
 * ��ʼ������
 *
 * J_amount ������
 * M_amount ������
 * ���ɳ�ʼ��ET, ST�����Լ�MO��������
 */
void initial(int J_amount, int M_amount);

/**
 * ����ʱ�亯��
 *
 * MO[MAX] �����ӹ�˳����������
 */
void time_calculate(machine* MO[MAX]);

/**
 * �����������麯��
 *
 * MO[MAX] �����ӹ�˳����������
 * ��������洢������
 */
void delete_MO(machine* MO[MAX], int M_amount);
#endif // !_IM_H_
