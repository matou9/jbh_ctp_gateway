#include "../0_CTP_gateway.h"

bool CTP_gateway::is_error_response(CThostFtdcRspInfoField* pRspInfo)
{
    if (pRspInfo == nullptr)
    {
        return false;
    }
    else if (pRspInfo->ErrorID == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}