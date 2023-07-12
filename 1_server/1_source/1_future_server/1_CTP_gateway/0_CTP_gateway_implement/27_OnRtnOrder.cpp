#include "../0_CTP_gateway.h"
#include "0_server_connector/0_server_connector.h"

#include <string.h>
#include <iostream>

#define MEM_PADDING_SIZE 8
void CTP_gateway::OnRtnOrder(CThostFtdcOrderField * pOrder)
{
    //回报CTP接受到委托, 已发往交易所, 交易网关标记委托编号
    if (strlen(pOrder->OrderSysID) == 0)
    {
        std::cout << "CTP_gateway::OnRtnOrder(): CTP接受到委托, 已发往交易所" << std::endl;
        callback_type type = E_ON_ENTRUST_INSERTED;
        
        int buf_size = sizeof(future_limit_entrust) + MEM_PADDING_SIZE;
        char* buf = new char[buf_size];
        memset(buf, 0, buf_size);
        char* ptr = buf;
        ptr[0] = type;
        ptr += MEM_PADDING_SIZE;

        //从entrust_map中找到对应的委托
        uint32_t this_order_ref = atoi(pOrder->OrderRef);
        char this_entrust_id[32] = {0};
        sprintf(this_entrust_id, "#%d#%d#%d", front_id, session_id, this_order_ref);
        client_entrust entrust_pair = entrust_map[this_entrust_id];
        int this_client_socket = entrust_pair.first;
        future_limit_entrust *this_entrust = entrust_pair.second;
        
        memcpy(ptr, this_entrust, sizeof(future_limit_entrust));

        //回报给客户端
        if (server_api != nullptr)
        {
            server_api->write_server_response_to_queue(this_client_socket, buf, sizeof(future_limit_entrust));
        }
        else
        {
            //TODO CTP交易网关独立运行
        }
    }
    //回报交易所接受到委托, 转换为订单; 或订单状态更新
    std::cout << "CTP_gateway::OnRtnOrder(): 订单状态更新, OrderSysID: " << pOrder->OrderSysID << std::endl;
    
    
}