#include "../0_CTP_gateway.h"

void CTP_gateway::req_connect()
{
    if (!CTP_trader_api) return;
    CTP_trader_api->SubscribePublicTopic(THOST_TERT_QUICK);			//注册公有流
    CTP_trader_api->SubscribePrivateTopic(THOST_TERT_QUICK);		//注册私有流
    CTP_trader_api->RegisterFront((char*)front_addr.c_str());       //注册交易前置ip
    CTP_trader_api->Init();                                         //CTPApi初始化    

}