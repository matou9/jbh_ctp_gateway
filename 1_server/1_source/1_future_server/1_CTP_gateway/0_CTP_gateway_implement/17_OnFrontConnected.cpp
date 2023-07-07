#include "../0_CTP_gateway.h"
#include <iostream>
void CTP_gateway::OnFrontConnected()
{
    std::cout << "CTP_gateway::OnFrontConnected()" << std::endl;
    login();
    
}