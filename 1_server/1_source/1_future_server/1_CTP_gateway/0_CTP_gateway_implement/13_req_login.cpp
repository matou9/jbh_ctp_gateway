#include "../0_CTP_gateway.h"
#include <string.h>
#include "2_utils/0_string_utils.hpp"
void CTP_gateway::req_login()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	string_utils::strncpy(req.BrokerID, broker.c_str(), broker.size());
	string_utils::strncpy(req.UserID, user.c_str(), user.size());
	string_utils::strncpy(req.Password, password.c_str(), password.size());
	memset(req.UserProductInfo, 0, sizeof(req.UserProductInfo));    //用户端产品信息, 有需求时再填写
	CTP_trader_api->ReqUserLogin(&req, generate_new_request_id());
}