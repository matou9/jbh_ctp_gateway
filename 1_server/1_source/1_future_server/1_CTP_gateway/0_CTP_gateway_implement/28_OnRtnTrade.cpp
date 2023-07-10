#include "../0_CTP_gateway.h"

#include <iostream>
void CTP_gateway::OnRtnTrade(CThostFtdcTradeField * pTrade)
{
    // TODO
    std::cout << "CTP_gateway::OnRtnTrade(): 成交回报, OrderSysID: " << pTrade->OrderSysID << std::endl;

}