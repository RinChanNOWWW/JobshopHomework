/**
 * �˳�����Ҫ�Ļ��������ݽṹ�뺯������
 *
 * base.h
 * by ������
 * 2018-5-10
 */

#ifndef _BASE_H_
#define _BASE_H_

#define MAX_MATRIX 150      //���������ģ

/* �洢����Ļ������� */
typedef struct {
	int machine_amount;              //�ܹ���Ҫ�Ļ�������
	int job_amount;                  //�ܹ��Ĺ�������
	int operation_amount[MAX_MATRIX];   //ÿ�������Ĺ�����
} All_job;

/* �洢����Ļ������ݣ���������ģ� */
typedef struct {
	int begin;                       //����ӹ��Ŀ�ʼʱ��
	int end;                         //����ӹ��Ľ���ʱ��
	int job;                         //�ù�����������
	int operation;                   //�ù����Ǵ˹����ĵڼ�������
} Result;


/**
 * ����������
 * 
 * a ����������
 * b ��һ������������
 */
void exchange(int* a, int* b);

/**
 * �������һ������
 * 
 * a[] ��Ҫ�����ҵ�����
 * n ��������Ч���ݵĸ���
 */
void random_shuffle(int* a, int n);

/**
 * �������������ֵ
 * 
 * a һ����
 * b ��һ����
 * return a��b�еĽϴ�ֵ
 */
int getMax(int a, int b);

/**
 * ��һ���������鸴�Ƶ���һ������������
 *
 * destination[] ���Ʋ���������
 * source[] �����Ƶ�����
 * n ����Ĺ�ģ
 */
void arrayCopy(int * destination, int * source, int n);

#endif // !_BASE_H_
