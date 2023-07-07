#include "../0_CTP_gateway.h"
#include <sstream>
#include <boost/filesystem.hpp>
void CTP_gateway::connect()
{
    std::stringstream ss;
    ss << flow_dir << "/flows/" << broker << "/" << user << "/";
    boost::filesystem::create_directories(ss.str());

    CTP_trader_api = CThostFtdcTraderApi::CreateFtdcTraderApi(ss.str().c_str());
    CTP_trader_api->RegisterSpi(this);

    req_connect();
}