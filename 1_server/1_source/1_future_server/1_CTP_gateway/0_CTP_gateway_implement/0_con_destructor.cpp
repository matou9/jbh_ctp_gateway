#include "../0_CTP_gateway.h"
#include <iostream>
CTP_gateway::CTP_gateway() : 
    CTP_trader_api(nullptr), 
    is_ready(false),
    request_id(0), 
    trading_day(0), 
    front_id(0), 
    session_id(0), 
    order_ref(0)
{

}

CTP_gateway::~CTP_gateway()
{
    if (CTP_trader_api != nullptr)
    {
        release();
    }
}