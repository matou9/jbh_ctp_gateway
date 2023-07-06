#include "../0_server_connector.h"

void server_connector::add_gateway(CTP_gateway* p_gateway)
{
    p_trade_gateway = p_gateway;
}