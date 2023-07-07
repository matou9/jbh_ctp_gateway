#include "../0_CTP_gateway.h"
#include <iostream>
void CTP_gateway::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (is_error_response(pRspInfo))
    {
        std::cout << "CTP_gateway::OnRspAuthenticate() : 认证失败!" << std::endl;
        return;
    }
    else
    {
        std::cout << "CTP_gateway::OnRspAuthenticate() : 认证成功!" << std::endl;
        req_login();
    }
}