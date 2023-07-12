#include "../0_server_connector.h"
#include "1_source/1_future_server/1_CTP_gateway/0_CTP_gateway.h"

#include <string.h>
#include <iostream>
/*
 * 定义交易接口api名称枚举变量, 添加至数据报的首地址, 用于区分不同的交易接口api
 */
typedef enum
{
    E_LIMIT_ENTRUST_INSERT = 1,
    E_LIMIT_ORDER_CANCEL,

}api_type;
#define MEM_PADDING_SIZE 8
void server_connector::process_client_request(int client_socket, char* p_message, int message_length)
{
    if (p_trade_gateway == nullptr)
    {
        printf("trade gateway not initialized\n");
        return;
    }
    char* move_pointer = p_message;
    api_type api_name = (api_type)(move_pointer[0]);
    move_pointer += MEM_PADDING_SIZE;
    if (api_name == E_LIMIT_ENTRUST_INSERT)
    {
        //
        // const char* socket_char = move_pointer + sizeof(future_limit_entrust);
        future_limit_entrust *entrust = (future_limit_entrust*)move_pointer;
        // memset(entrust->entrust_id, 0, sizeof(entrust->entrust_id));
        // memcpy(entrust->entrust_id, socket_char, strlen(socket_char));
        p_trade_gateway->limit_entrust_insert(entrust, client_socket);
        std::cout << "处理客户端下单请求" << std::endl;        
    }
    else if (api_name == E_LIMIT_ORDER_CANCEL)
    {
        //TODO
        p_trade_gateway->limit_order_action((future_limit_order_action*)move_pointer, client_socket);
    }
    else
    {
        printf("unknown api name\n");
    }

}