#include "../0_client_connector.h"
#include <string.h>
void client_connector::send_to_server(char* message, int len)
{
    printf("send message %s to server\n", message);
    write(sock, message, len);                //向服务器端发送字符串消息               //向服务器端发送字符串消息
}