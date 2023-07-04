#include "../0_server_connector.h"
#include <iostream>

void server_connector::error_handling(std::string message)
{
    std::cout << message << std::endl;
    exit(1);
}