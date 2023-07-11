#include "../0_CTP_gateway.h"

#include <string.h>
void CTP_gateway::limit_entrust_insert(future_limit_entrust* entrust, int client_socket)
{
    if (is_ready)
    {
        //委托编号entrust_id: client_sock#front#session#order_ref
        order_ref++;
        char *entrust_id = entrust->entrust_id;
        entrust_id += strlen(entrust_id);
        sprintf(entrust_id, "#%d#%d#%d", front_id, session_id, order_ref);
        //本地维护一份委托信息, 回报时直接读取
        future_limit_entrust *gateway_entrust = new future_limit_entrust(*entrust);
        client_entrust entrust_pair(client_socket, gateway_entrust);
        entrust_map[entrust->entrust_id] = entrust_pair;
        req_entrust_insert(entrust);
        

    }
}