#include "../0_CTP_gateway.h"

#include <iostream>
void CTP_gateway::OnErrRtnOrderInsert(CThostFtdcInputOrderField * pInputOrder, CThostFtdcRspInfoField * pRspInfo)
{
    if (is_error_response(pRspInfo))
    {
        std::cout << "CTP_gateway::OnRspOrderInsert(): 下单失败!, errorID: " << pRspInfo->ErrorID << std::endl;
    }
    else
    {
        std::cout << "CTP_gateway::OnRspOrderInsert(): 下单失败?" << std::endl;
    }
}