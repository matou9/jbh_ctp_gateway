/*
 * 1_future_api.h
 * 期货交易接口api声明
 * created by 唐尚涛
 */
#ifndef _FUTURE_API_H_
#define _FUTURE_API_H_

#include "1_future_data_class/0_future_limit_entrust.h"
#include "1_future_data_class/2_future_limit_order_action.h"


#include <stdint.h>

// /*
//  * 预留数据结构
//  */
// class future_condition_entrust;
// class future_condition_order_action;
// class future_parked_order;
// class future_parked_order_action;
// class future_fak_entrust;
// class future_fak_order_action;
// class future_fok_entrust;
// class future_fok_order_action;
/*
 * 交易接口api的基类
 */
class future_api
{
    public:
    /*
     * 析构函数
     */
    future_api();
    ~future_api();
    
    /*
     * 下达限价单
     */
    void limit_entrust_insert(future_limit_entrust *entrust);
    
    /*
     * 撤销限价单
     */
    void limit_order_cancel(future_limit_order_action *order);

    // /*
    //  * 下达条件单
    //  */
    // virtual void condition_entrust_insert(future_condition_entrust *condition_order) {};

    // /*
    //  * 撤销条件单
    //  */
    // virtual void condition_order_cancel(future_condition_order_action *condition_order_action) {};

    // /*
    //  * 下达预埋单
    //  */
    // virtual void parked_order_insert(future_parked_order *parked_order) {};

    // /*
    //  * 撤销预埋单
    //  */
    // void parked_order_cancel(future_parked_order_action *parked_order_action) {};

    // /*
    //  * 下达FAK单
    //  */
    // void fak_entrust_insert(future_fak_entrust *fak_entrust) {};

    // /*
    //  * 撤销FAK单
    //  */
    // void fak_order_cancel(future_fak_order_action *fak_order_action) {};

    // /*
    //  * 下达FOK单
    //  */
    // void fok_entrust_insert(future_fok_entrust *fok_entrust) {};

    // /*
    //  * 撤销FOK单
    //  */
    // void fok_order_cancel(future_fok_order_action *fok_order_action) {};

    
    

};



#endif