/**
 * @brief 提供基本的数据类型与操作
 *
 * @file base.h
 * @author Hzy & Gxz
 * @date 2018-05-03
 */

#ifndef _BASE_H_
#define _BASE_H_

/**
 * @brief 存储一项工序数据的结构体
 *
 */
typedef struct OPERATION
{
	int product;                   /**< @brief 表示该工序所属产品的序号 */
	int time;                      /**< @brief 表示该工序所需要消耗的时间 */
	int machine;                   /**< @brief 表示该工序指定机器的序号 */
} operation;

/**
* @brief 存储订单数据的结构体
*
*/
typedef struct ORDER
{
	operation** operation_ptr;    /**< @brief 指向工序的指针的数组 */
	int product_amount;           /**< @brief 存储产品的数量 */
	int machine_amount;           /**< @brief 存储机器的数量 */
} order;
#endif // !_BASE_H_
