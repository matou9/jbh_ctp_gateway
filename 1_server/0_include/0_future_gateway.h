/*
 * 0_future_gateway.h
 * 期货交易网关基类声明
 * created by 唐尚涛
 */

#ifndef FUTURE_GATEWAY_H_
#define FUTURE_GATEWAY_H_

#include "1_future_data_class/0_future_limit_entrust.h"
#include "1_future_data_class/2_future_limit_order_action.h"
/*
 * 期货交易网关状态
 */
typedef enum
{
    E_NOT_CONNECTED,
    E_CONNECTED,
    E_AUTHENTICATED,
    E_LOGGED,
    E_QUERIED,
    E_CONFIRMED
}gateway_state;

class future_gateway
{
public:
    virtual ~future_gateway() = 0;

public:
    virtual void init() = 0;
    virtual void release() = 0;

    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void login() = 0;
    virtual void logout() = 0;
    virtual void confirm() = 0;

    virtual void entrust_insert(future_limit_entrust* entrust) = 0;
    virtual void entrust_action(future_limit_order_action* order_action) = 0;
    
};









#endif