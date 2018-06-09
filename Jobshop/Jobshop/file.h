/**
 * file and io
 *
 * file.h
 * by ��ϣ֮
 * 2018-5-12
 */
#pragma once
#ifndef _FILE_H_
#define _FILE_H_

#include "base.h"

/** û�а�Ҫ���������ʱ�������뺯��
void input(All_job * job);       
*/

/**
 * ���ļ�����ѡ�Ӽ���/stdin���ж�ȡ��Ҫ������
 *
 * job �洢���л������ݵĽṹ������
 */
void read_from_file(All_job * job);

/**
 * ���������
 *
 * elite[] ���Ž�����Ӧ�ı���Ⱦɫ��
 * machine �ܻ�����
 * job �ܹ�����
 * all_operation �ܹ�����
 */
void output(int * elite, int machine, int job, int all_operation);

#endif // !_FILE_H_