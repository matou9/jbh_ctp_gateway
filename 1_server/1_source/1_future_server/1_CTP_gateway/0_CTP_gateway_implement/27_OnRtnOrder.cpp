#include "../0_CTP_gateway.h"

#include <string.h>
#include <iostream>
void CTP_gateway::OnRtnOrder(CThostFtdcOrderField * pOrder)
{
    if (strlen(pOrder->OrderSysID) == 0)
    {
        std::cout << "CTP_gateway::OnRtnOrder(): CTP接受到委托, 已发往交易所" << std::endl;
        //回报CTP接受到委托, 已发往交易所, 交易网关标记委托编号



    }

    std::cout << "CTP_gateway::OnRtnOrder(): 订单状态更新, OrderSysID: " << pOrder->OrderSysID << std::endl;

    //CTP回调线程
    
    
}