/**
 * @brief �ṩ�������������������
 *
 * @file base.h
 * @author Hzy & Gxz
 * @date 2018-05-03
 */

#ifndef _BASE_H_
#define _BASE_H_

/**
 * @brief �洢һ������ݵĽṹ��
 *
 */
typedef struct OPERATION
{
	int product;                   /**< @brief ��ʾ�ù���������Ʒ����� */
	int time;                      /**< @brief ��ʾ�ù�������Ҫ���ĵ�ʱ�� */
	int machine;                   /**< @brief ��ʾ�ù���ָ����������� */
} operation;

/**
* @brief �洢�������ݵĽṹ��
*
*/
typedef struct ORDER
{
	operation** operation_ptr;    /**< @brief ָ�����ָ������� */
	int product_amount;           /**< @brief �洢��Ʒ������ */
	int machine_amount;           /**< @brief �洢���������� */
} order;
#endif // !_BASE_H_
