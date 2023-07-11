#include "../0_CTP_gateway.h"
#include <iostream>
CTP_gateway::CTP_gateway() : 
    CTP_trader_api(nullptr), 
    is_ready(false),
    front_addr(),
    broker(),
    user(),
    password(),
    app(),
    auth_code(),
    flow_dir(),
    trading_day(0), 
    front_id(0), 
    session_id(0), 
    order_ref(0),
    entrust_map(),
    order_map(),
    trade_map()
{

}

CTP_gateway::~CTP_gateway()
{
    if (CTP_trader_api != nullptr)
    {
        release();
    }
    for (auto& it : entrust_map)
    {
        client_entrust entrust = it.second;
        if (entrust.second != nullptr)
        {
            delete entrust.second;
            entrust.second = nullptr;
        }
    }
    entrust_map.clear();
    for (auto& it : order_map)
    {
        client_order order = it.second;
        if (order.second != nullptr)
        {
            delete order.second;
            order.second = nullptr;
        }
    }
    order_map.clear();
    for (auto& it : trade_map)
    {
        client_trade trade = it.second;
        if (trade.second != nullptr)
        {
            delete trade.second;
            trade.second = nullptr;
        }
    }
    trade_map.clear();
    
}