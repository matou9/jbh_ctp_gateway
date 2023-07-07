#include "../0_CTP_gateway.h"

uint32_t CTP_gateway::generate_new_request_id()
{
    return (request_id.fetch_add(1) + 1);
}