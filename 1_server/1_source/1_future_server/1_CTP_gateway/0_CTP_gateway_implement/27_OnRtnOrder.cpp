#include "../0_CTP_gateway.h"
#include "0_server_connector/0_server_connector.h"

#include <string.h>
#include <iostream>


void CTP_gateway::OnRtnOrder(CThostFtdcOrderField * pOrder)
{
    //回报CTP接受到委托, 已发往交易所, 交易网关标记委托编号
    if (strlen(pOrder->OrderSysID) == 0)
    {
        std::cout << "CTP_gateway::OnRtnOrder(): CTP接受到委托, 已发往交易所" << std::endl;
        //从entrust_map中找到对应的委托
        uint32_t this_order_ref = atoi(pOrder->OrderRef);
        char this_entrust_id[32] = {0};
        sprintf(this_entrust_id, "#%d#%d#%d", front_id, session_id, this_order_ref);
        client_entrust entrust_pair = entrust_map[this_entrust_id];
        int this_client_socket = entrust_pair.first;
        future_limit_entrust *this_entrust = entrust_pair.second;
        
        //回报给客户端
        server_api->write_server_response_to_queue(this_client_socket, (char*)this_entrust, sizeof(future_limit_entrust));


    }
    //回报交易所接受到委托, 转换为订单; 或订单状态更新
    std::cout << "CTP_gateway::OnRtnOrder(): 订单状态更新, OrderSysID: " << pOrder->OrderSysID << std::endl;
    
    
}