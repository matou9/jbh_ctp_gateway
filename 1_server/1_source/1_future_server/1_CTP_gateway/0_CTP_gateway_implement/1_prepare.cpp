#include "../0_CTP_gateway.h"

void CTP_gateway::prepare(const char* config_file_name)
{
    init(config_file_name);
    connect();
}