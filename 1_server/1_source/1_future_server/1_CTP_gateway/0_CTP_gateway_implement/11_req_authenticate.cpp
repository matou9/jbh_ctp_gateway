#include "../0_CTP_gateway.h"

#include "2_utils/0_string_utils.hpp"
void CTP_gateway::req_authenticate()
{
    CThostFtdcReqAuthenticateField req;
    memset(&req, 0, sizeof(req));
    string_utils::strncpy(req.BrokerID, broker.c_str(), sizeof(req.BrokerID));
    string_utils::strncpy(req.UserID, user.c_str(), sizeof(req.UserID));
    string_utils::strncpy(req.AppID, app.c_str(), sizeof(req.AppID));
    string_utils::strncpy(req.AuthCode, auth_code.c_str(), sizeof(req.AuthCode));
    CTP_trader_api->ReqAuthenticate(&req, 0);
}