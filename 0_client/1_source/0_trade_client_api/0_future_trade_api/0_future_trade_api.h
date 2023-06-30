/*
 * 0_future_trade_api.h
 * 期货交易接口api的声明
 * created by 唐尚涛
 */

#ifndef _FUTURE_TRADE_API_H_
#define _FUTURE_TRADE_API_H_

#include "0_base_trade_api.h"

class future_trade_api : public base_trade_api
{
    /*
     * 构造函数、析构函数
     */
    future_trade_api();
    virtual ~future_trade_api() override;

    /*
     * 下达限价单
     */
    virtual void limit_entrust_insert(base_trade_limit_entrust *entrust) override;

    /*
     * 撤销限价单
     */
    virtual void limit_order_cancel(base_trade_limit_order_action *order) override;
    


};




#endif