/*
 * 0_future_gateway.h
 * 期货交易网关基类声明
 * created by 唐尚涛
 */

#ifndef FUTURE_GATEWAY_H_
#define FUTURE_GATEWAY_H_

#include "1_future_data_class/0_future_limit_entrust.h"
#include "1_future_data_class/2_future_limit_order_action.h"
// /*
//  * 期货交易网关状态
//  */
// typedef enum
// {
//     E_NOT_CONNECTED,
//     E_CONNECTED,
//     E_AUTHENTICATED,
//     E_LOGGED,
//     E_QUERIED,
//     E_CONFIRMED
// }gateway_state;

/* 
 * 定义事件回调枚举变量, 添加至数据报的首地址, 用于区分不同的事件回调
 */
typedef enum
{
    //TODO 是否需要将CTP交易网关准备交易的事件通知给客户端?
    //目前的设想是CTP交易网关准备好交易后, 再运行服务端, 接受客户端连接, 所以没有通知
    // E_ON_NOT_READY_TO_TRADE,    //CTP交易网关无法交易
    // E_ON_READY_TO_TRADE,        //CTP交易网关准备好交易
    
    E_ON_TRADE_ERROR,           //CTP交易网关传递错误回报
    E_ON_ENTRUST_INSERTED,      //CTP交易网关传递委托回报
    E_ON_ORDER_STATUS_UPDATE,   //CTP交易网关传递订单状态更新回报
    E_ON_TRADE_UPDATE,          //CTP交易网关传递成交回报
}callback_type;

class future_gateway
{
public:
    virtual ~future_gateway(){};

public:
    virtual void prepare(const char* config_file_name) = 0;
    virtual void limit_entrust_insert(future_limit_entrust* entrust, int client_socket) = 0;
    virtual void limit_order_action(future_limit_order_action* order_action, int client_socket) = 0;
protected:
    virtual void init(const char* config_file_name){};
    virtual void release(){};
    virtual void connect(){};
    virtual void disconnect(){};
    virtual void login(){};
    virtual void logout(){};
    virtual void confirm(){};

    
};









#endif