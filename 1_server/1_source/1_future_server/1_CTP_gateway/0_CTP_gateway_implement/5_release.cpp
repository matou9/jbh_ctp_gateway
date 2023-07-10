#include "../0_CTP_gateway.h"

#include <iostream>
void CTP_gateway::release()
{
    std::cout << "CTP_gateway::release() : 释放CTP交易接口" << std::endl;
    CTP_trader_api->Release();
    CTP_trader_api = nullptr;
    
}