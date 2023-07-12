/*
 * 1_future_api.h
 * 期货交易接口api声明
 * created by 唐尚涛
 */
#ifndef _FUTURE_API_H_
#define _FUTURE_API_H_

#include "1_future_data_class/0_future_limit_entrust.h"
#include "1_future_data_class/2_future_limit_order_action.h"
#include "1_source/1_client_connector/0_client_connector.h"

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
 * 定义交易接口api名称枚举变量, 添加至数据报的首地址, 用于区分不同的交易接口api
 */
typedef enum
{
    E_LIMIT_ENTRUST_INSERT = 1,
    E_LIMIT_ORDER_CANCEL,

}api_type;

/* 
 * 定义事件回调枚举变量, 添加至数据报的首地址, 用于区分不同的事件回调
 */
typedef enum
{
    E_ON_CONNECTED,
    E_ON_DISCONNECTED,
    E_ON_ORDER_STATUS_UPDATE,
    E_ON_TRADE_UPDATE,
}callback_type;

/*
 * 交易接口api的基类
 */
class future_api
{
private:
    client_connector* connector;
    bool              is_connected;

public:
    /*
     * 析构函数
     */
    future_api();
    ~future_api();
    
    // static future_api* create_trade_api();
    // void release_trade_api();

    /*
     * 初始化交易接口api, 连接到交易服务器
     */
    void init(std::string ip, std::string port);
    
    /*
     * 下达限价单
     */
    void limit_entrust_insert(future_limit_entrust *entrust);
    
    /*
     * 撤销限价单
     */
    void limit_order_cancel(future_limit_order_action *order);

    /*
     * 阻塞, 等待接受服务端回报
     */
    void join() {connector->join();}

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