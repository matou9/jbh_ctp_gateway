#include "../0_CTP_gateway.h"
#include "0_server_connector/0_server_connector.h"

#include <iostream>
void CTP_gateway::OnRspQrySettlementInfoConfirm
(
    CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast
)
{
    if (is_error_response(pRspInfo))
    {
        std::cout << "CTP_gateway::OnRspQrySettlementInfoConfirm() : 查询结算单确认情况失败!" << std::endl;
        return;
    }
    else
    {
        std::cout << "CTP_gateway::OnRspQrySettlementInfoConfirm() : 查询结算单确认情况成功!" << std::endl;
        if (pSettlementInfoConfirm == nullptr)
        {
            std::cout << "CTP_gateway::OnRspQrySettlementInfoConfirm() : 未有过确认结算单的记录, 现首次确认结算单" << std::endl;
            req_settlement_confirm();
        }
        else
        {
            uint32_t confirm_date = strtoul(pSettlementInfoConfirm->ConfirmDate, nullptr, 10);
            if (confirm_date == trading_day)
            {
                is_ready = true;
                std::cout << "CTP_gateway::OnRspQrySettlementInfoConfirm() : 已确认过当日结算单, 无需再次确认. CTP用户"<< user << "准备交易" << std::endl;        
                if (server_api != nullptr)
                {
                    //准备交易
                    server_api->add_gateway(this);
                }
                return;
            }
            else if (confirm_date < trading_day)
            {
                std::cout << "CTP_gateway::OnRspQrySettlementInfoConfirm() : 现首次确认当日结算单" << std::endl;
                req_settlement_confirm();
            }
            else
            {
                std::cout << "CTP_gateway::OnRspQrySettlementInfoConfirm() : 确认结算单的日期大于当前交易日, 什么情况?" << std::endl;
                return;
            }

        }
    }
    
}