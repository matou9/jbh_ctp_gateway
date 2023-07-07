/*
 * 3_future_limit_trade.h
 * 期货限价成交数据结构声明
 * created by 唐尚涛
 */

#ifndef _FUTURE_LIMIT_TRADE_H_
#define _FUTURE_LIMIT_TRADE_H_

#include "1_future_limit_order.h"

/*
 * 期货限价成交数据结构
 */
class future_limit_trade
{
    // 该成交源自的订单
    future_limit_order origin_order;
    // 成交日期
    uint32_t trade_date;
    // 成交时间
    uint64_t trade_time;
    // 成交价格
    double trade_price;
    // 成交数量
    uint32_t trade_volume;
    // 成交方向
    future_direction_type direction;
    // 成交开平
    future_offset_type offset;
    // 成交编号(Exchange#TradeID#Direction确定唯一的成交)
    char trade_id[32];

};



#endif