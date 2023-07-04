#include "../0_server_connector.h"
#include <string.h>

void server_connector::init(std::string port)
{
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock==-1)
    {
        error_handling("socket() error");
    }
        
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(port.c_str()));

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
    {
        error_handling("bind() error");
    }

    if(listen(serv_sock, 5)==-1)
    {
        error_handling("listen() error");
    }
        
    
}