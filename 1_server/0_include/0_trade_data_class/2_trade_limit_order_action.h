/*
 * 2_trade_limit_order_action.h
 * 交易接口限价委托操作数据结构声明
 * created by 唐尚涛 
 */
#ifndef _TRADE_LIMIT_ORDER_ACTION_H_
#define _TRADE_LIMIT_ORDER_ACTION_H_

#include <string>

typedef enum 
{
    E_CANCEL,
    // E_MODIFY, // CTP暂不支持改单

}trade_order_action_type;

class trade_limit_order_action
{
    // 订单操作类型
    trade_order_action_type action_type;
    // 委托编号(撤销委托时填写)
    std::string entrust_id;
    // 订单编号(撤销订单时填写)
    std::string order_id;
    // // 改单目标价格

    // // 改单目标数量

};









#endif