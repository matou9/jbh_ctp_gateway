#include "../0_CTP_gateway.h"
#include <iostream>
void CTP_gateway::OnRspUserLogin
(
    CThostFtdcRspUserLoginField * pRspUserLogin,
    CThostFtdcRspInfoField * pRspInfo,
    int nRequestID,
    bool bIsLast
)
{
    if (is_error_response(pRspInfo))
    {
        std::cout << "CTP_gateway::OnRspUserLogin() : 登录失败!" << std::endl;
        return;
    }
    else
    {
        std::cout << "CTP_gateway::OnRspUserLogin() : 登录成功!" << std::endl;
        
        front_id = pRspUserLogin->FrontID;
        session_id = pRspUserLogin->SessionID;
        trading_day = std::strtoul(pRspUserLogin->TradingDay, nullptr, 10);
        //TODO 最大报单引用
        req_query_settlement_confirm();
    }
}