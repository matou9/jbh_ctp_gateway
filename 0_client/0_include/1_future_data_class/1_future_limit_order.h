/*
 * 1_future_limit_order.h
 * 期货限价订单数据结构声明
 * created by 唐尚涛 
 */
#ifndef _FUTURE_LIMIT_ORDER_H_
#define _FUTURE_LIMIT_ORDER_H_

#include "0_future_limit_entrust.h"

#include <stdint.h>

typedef enum
{
    E_ALL_TRADEED,
    E_PART_TRADED_QUEUEING,
    E_PART_TRADED_NOT_QUEUEING,
    E_NO_TRADE_QUEUEING,
    E_NO_TRADE_NOT_QUEUEING,
    E_CANCELED,
    // E_TOUCHED,
}future_order_status_type;

/*
 * 期货限价订单数据结构
 * 
 */
class future_limit_order
{
    // 该订单源自的委托
    future_limit_entrust origin_entrust;
    // 挂单日期
    uint32_t insert_date;
    // 挂单时间
    uint64_t insert_time;
    // 订单编号
    std::string order_id;
    // 剩余数量
    uint32_t volume_left;
    // 订单状态
    future_order_status_type status;    

};








#endif