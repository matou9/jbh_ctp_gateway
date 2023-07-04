#include "../0_client_connector.h"

void client_connector::error_handling(std::string message)
{
    printf("%s\n", message.c_str());
    exit(1);
}