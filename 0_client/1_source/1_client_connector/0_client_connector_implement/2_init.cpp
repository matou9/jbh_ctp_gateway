#include "../0_client_connector.h"
#include "string.h"
void client_connector::init(std::string ip, std::string port)
{
    sock=socket(PF_INET, SOCK_STREAM, 0);    //创建客户端TCP套接字
    if(sock==-1)
        error_handling("socket() error");
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(ip.c_str());
    serv_adr.sin_port=htons(atoi(port.c_str()));
}