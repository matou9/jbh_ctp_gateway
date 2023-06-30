/*
 *base_future_trade_api.h
 *交易接口api的基类, 用于声明所有品种(期货、股票)交易接口api的基本功能
 *created by 唐尚涛 
 */

#ifndef _BASE_FUTURE_TRADE_API_H_
#define _BASE_FUTURE_TRADE_API_H_

#include "0_base_trade_data_class/0_base_trade_limit_entrust.h"
#include "0_base_trade_data_class/2_base_trade_limit_order_action.h"


#include <stdint.h>

/*
 * 预留数据结构
 */
class base_trade_condition_entrust;
class base_trade_condition_order_action;
class base_trade_parked_order;
class base_trade_parked_order_action;
class base_trade_fak_entrust;
class base_trade_fak_order_action;
class base_trade_fok_entrust;
class base_trade_fok_order_action;
/*
 * 交易接口api的基类
 */
class base_trade_api
{
    public:
    /*
     * 析构函数
     */
    virtual ~base_trade_api() {};
    
    /*
     * 下达限价单
     */
    virtual void limit_entrust_insert(base_trade_limit_entrust *entrust) = 0;
    
    /*
     * 撤销限价单
     */
    virtual void limit_order_cancel(base_trade_limit_order_action *order) = 0;

    /*
     * 下达条件单
     */
    virtual void condition_entrust_insert(base_trade_condition_entrust *condition_order) {};

    /*
     * 撤销条件单
     */
    virtual void condition_order_cancel(base_trade_condition_order_action *condition_order_action) {};

    /*
     * 下达预埋单
     */
    virtual void parked_order_insert(base_trade_parked_order *parked_order) {};

    /*
     * 撤销预埋单
     */
    void parked_order_cancel(base_trade_parked_order_action *parked_order_action) {};

    /*
     * 下达FAK单
     */
    void fak_entrust_insert(base_trade_fak_entrust *fak_entrust) {};

    /*
     * 撤销FAK单
     */
    void fak_order_cancel(base_trade_fak_order_action *fak_order_action) {};

    /*
     * 下达FOK单
     */
    void fok_entrust_insert(base_trade_fok_entrust *fok_entrust) {};

    /*
     * 撤销FOK单
     */
    void fok_order_cancel(base_trade_fok_order_action *fok_order_action) {};

    
    

};


























#endif
