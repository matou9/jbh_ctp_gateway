#include "../0_CTP_gateway.h"

void CTP_gateway::limit_entrust_insert(future_limit_entrust* entrust)
{
    if (is_ready)
    {
        req_entrust_insert(entrust);
    }
}