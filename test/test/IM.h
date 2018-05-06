/**
 * IM.h
 *
 * 输入模块
 * By Hzy
 * 2018-5-6
 */

#ifndef _IM_H_
#define _IM_H_

#define MAX 10           //暂且定义一个矩阵的最大长度
int J_amount, M_amount;  //工件与机器数
int max_job_t;           //加工时间最长工件的总加工时间
int max_t_job;           //耗时最长的工件

/**
 * 初始化模块
 *
 * 按顺序以非零自然数表示工序，0代表不存在
 */
int JO[MAX][MAX];       //工件-工序矩阵，JO(ij)表示工件i的第j道工序
int OA[MAX];            //各工件所需工序数
int PT[MAX][MAX];       //工序耗时矩阵，对应JO中各工序需要的时间
int OM[MAX][MAX];       //工序-机器矩阵，对应JO各工序所在的机器
int ST[MAX][MAX];       //开始时间矩阵，对应MO中各工序的开始时间，从0开始
int ET[MAX][MAX];       //终止时间矩阵，对应MO中各工序的终止时间

/* 一个机器上工序操作顺序的有向链表 */
typedef struct MACHINE {
	int operation;           //工序的序号
	machine* next_operation;  //指向下一道工序
} machine;

machine* MO[MAX];         //每个机器上的工序顺序，是一个链表数组，元素为链表的头节点

/**
 * 暂定的输入函数
 *
 */
void input();

/**
 * 初始化函数
 *
 * J_amount 工件数
 * M_amount 机器数
 * 生成初始的ET, ST矩阵，以及MO链表数组
 */
void initial(int J_amount, int M_amount);

/**
 * 计算时间函数
 *
 * MO[MAX] 机器加工顺序的链表矩阵
 */
void time_calculate(machine* MO[MAX]);

/**
 * 销毁链表数组函数
 *
 * MO[MAX] 机器加工顺序的链表矩阵
 * 销毁数组存储的链表
 */
void delete_MO(machine* MO[MAX], int M_amount);
#endif // !_IM_H_
