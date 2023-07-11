#include "../0_CTP_gateway.h"
#include "2_utils/0_string_utils.hpp"
#include <string.h>
void CTP_gateway::req_query_settlement_confirm()
{
    CThostFtdcQrySettlementInfoConfirmField req;
    memset(&req, 0, sizeof(req));
    string_utils::strncpy(req.BrokerID, broker.c_str(), broker.size());
    string_utils::strncpy(req.InvestorID, user.c_str(), user.size());
    CTP_trader_api->ReqQrySettlementInfoConfirm(&req, 0);
}