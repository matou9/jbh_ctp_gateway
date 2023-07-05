#include "../0_server_connector.h"
#include <string.h>

void server_connector::init(std::string port)
{
    server_socket=socket(PF_INET, SOCK_STREAM, 0);
    if(server_socket==-1)
    {
        error_handling("socket() error");
    }
        
    
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=htonl(INADDR_ANY);
    server_address.sin_port=htons(atoi(port.c_str()));

    if(bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address))==-1)
    {
        error_handling("bind() error");
    }

    if(listen(server_socket, 5)==-1)
    {
        error_handling("listen() error");
    }
        
    
}