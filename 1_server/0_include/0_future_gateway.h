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
    virtual void prepare() = 0;
    virtual void limit_entrust_insert(future_limit_entrust* entrust) = 0;
    virtual void limit_order_action(future_limit_order_action* order_action) = 0;
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