#include "../0_client_connector.h"

void client_connector::connect_to_server()
{
    int result = connect(sock, (struct sockaddr*)&server_address, sizeof(server_address));
    if (result == -1)
    {
        error_handling("connect() error!");
        exit(1);
    }
    else
    {
        printf("server connected!\n");
        is_connected = true;
    }

}