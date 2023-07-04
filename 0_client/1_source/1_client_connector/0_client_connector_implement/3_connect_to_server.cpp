#include "../0_client_connector.h"

void client_connector::connect_to_server()
{
    int result = connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
    if (result == -1)
    {
        error_handling("connect() error!");
        exit(1);
    }
    else
    {
        printf("server connected!\n");
    }

}