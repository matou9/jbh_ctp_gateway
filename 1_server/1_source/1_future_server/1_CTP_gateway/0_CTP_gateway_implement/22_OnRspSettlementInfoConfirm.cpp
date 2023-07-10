#include "../0_CTP_gateway.h"
#include <iostream>
void CTP_gateway::OnRspSettlementInfoConfirm(
    CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    if (is_error_response(pRspInfo))
    {
        std::cout << "CTP_gateway::OnRspSettlementInfoConfirm(): 结算单确认信息错误!" << std::endl;
    }
    else
    {
        is_ready = true;
        std::cout << "CTP_gateway::OnRspSettlementInfoConfirm: 结算单确认信息成功!, CTP用户"<< user << "准备交易" << std::endl;
    }


}