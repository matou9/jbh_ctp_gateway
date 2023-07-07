#include "../0_CTP_gateway.h"
#include <iostream>
void CTP_gateway::OnFrontDisconnected(int nReason)
{
    std::cout << "CTP_gateway::OnFrontDisconnected" << std::endl;
}