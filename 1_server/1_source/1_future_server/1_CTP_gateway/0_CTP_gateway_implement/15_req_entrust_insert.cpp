#include "../0_CTP_gateway.h"


#include "2_utils/0_string_utils.hpp"

#include <string.h>
#include <iostream>
void CTP_gateway::req_entrust_insert(future_limit_entrust* entrust)
{
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));

    string_utils::strncpy(req.BrokerID, broker.c_str(), sizeof(req.BrokerID));
    string_utils::strncpy(req.InvestorID, user.c_str(), sizeof(req.InvestorID));
    string_utils::strncpy(req.InstrumentID, entrust->instrument_code, sizeof(req.InstrumentID));
    string_utils::strncpy(req.OrderRef, std::to_string(order_ref++).c_str(), sizeof(req.OrderRef));
    string_utils::strncpy(req.UserID, user.c_str(), sizeof(req.UserID));
    req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
    
    if (entrust->direction == E_LONG)
    {
        req.Direction = THOST_FTDC_D_Buy;
    }
    else if (entrust->direction == E_SHORT)
    {
        req.Direction = THOST_FTDC_D_Sell;
    }
    
    if (entrust->offset == E_OPEN)
    {
        req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    }
    else if (entrust->offset == E_CLOSE)
    {
        req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
    }
    else if (entrust->offset == E_CLOSE_TODAY)
    {
        req.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;
    }
    else if (entrust->offset == E_CLOSE_YESTERDAY)
    {
        req.CombOffsetFlag[0] = THOST_FTDC_OF_CloseYesterday;
    }

    req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    req.LimitPrice = entrust->limit_price;
    req.VolumeTotalOriginal = entrust->volume;
    req.TimeCondition = THOST_FTDC_TC_GFD;
    req.VolumeCondition = THOST_FTDC_VC_AV;
    req.ContingentCondition = THOST_FTDC_CC_Immediately;

    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    req.IsAutoSuspend = 0;
    req.UserForceClose = 0;
    req.IsSwapOrder = 0;

    int ret = CTP_trader_api->ReqOrderInsert(&req, generate_new_request_id());
    if (ret != 0)
    {
        std::cout << "CTP_gateway::req_entrust_insert(): 下单失败!, errorID: " << ret << std::endl;
    }
}
