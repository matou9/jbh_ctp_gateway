/*
 * 2_trade_limit_order_action.h
 * 交易接口限价委托操作数据结构声明
 * created by 唐尚涛 
 */
#ifndef _FUTURE_LIMIT_ORDER_ACTION_H_
#define _FUTURE_LIMIT_ORDER_ACTION_H_

#include <string>

typedef enum 
{
    E_CANCEL,
    // E_MODIFY, // CTP暂不支持改单

}future_order_action_type;

class future_limit_order_action
{
    // 订单操作类型
    future_order_action_type action_type;
    // 委托编号(撤销委托时填写)
    char entrust_id[64];
    // 订单编号(撤销订单时填写)
    char order_id[64];
    // // 改单目标价格

    // // 改单目标数量

};









#endif