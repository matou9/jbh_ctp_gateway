#include "../0_CTP_gateway.h"
#include "2_utils/0_string_utils.hpp"

#include <string.h>
#include <string>
#include <chrono>


void CTP_gateway::req_settlement_confirm()
{
    CThostFtdcSettlementInfoConfirmField req;
    memset(&req, 0, sizeof(req));
    string_utils::strncpy(req.BrokerID, broker.c_str(), broker.size());
    string_utils::strncpy(req.InvestorID, user.c_str(), user.size());
    std::string trading_day_str = std::to_string(trading_day);
    string_utils::strncpy(req.ConfirmDate, trading_day_str.c_str(), trading_day_str.size());
    
    auto now = std::chrono::system_clock::now();
    std::time_t time_t = std::chrono::system_clock::to_time_t(now);
    char* ctime_str = std::ctime(&time_t);
    memcpy(req.ConfirmTime, ctime_str + 11, 8);
    CTP_trader_api->ReqSettlementInfoConfirm(&req, 0);    
    
}