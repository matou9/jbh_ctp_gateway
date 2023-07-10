#include "../0_server_connector.h"

#include <iostream>
/*
 * 定义交易接口api名称枚举变量, 添加至数据报的首地址, 用于区分不同的交易接口api
 */
typedef enum
{
    E_LIMIT_ENTRUST_INSERT = 1,
    E_LIMIT_ORDER_CANCEL,

}api_type;

void server_connector::process_client_request(char* p_message, int message_length)
{
    if (p_trade_gateway == nullptr)
    {
        printf("trade gateway not initialized\n");
        return;
    }
    char* move_pointer = p_message;
    api_type api_name = (api_type)(move_pointer[0]);
    move_pointer++;
    switch (api_name)
    {
        case E_LIMIT_ENTRUST_INSERT:
            p_trade_gateway->limit_entrust_insert((future_limit_entrust*)move_pointer);
            std::cout << "处理客户端下单请求" << std::endl;
            break;
        case E_LIMIT_ORDER_CANCEL:
            p_trade_gateway->limit_order_action((future_limit_order_action*)move_pointer);
            break;
    }

}