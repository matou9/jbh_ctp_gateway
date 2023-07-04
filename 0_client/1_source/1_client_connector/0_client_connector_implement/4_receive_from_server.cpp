#include "../0_client_connector.h"

void client_connector::receive_from_server()
{
    while(stop_receive_thread.load() == false) 
    {
        char message[BUF_SIZE];
        int str_len;
        str_len = read(sock, message, BUF_SIZE-1);              //接收来自服务器端的消息
        message[str_len]= '\0';                               //在字符数组尾部添加字符串结束符'\0'
        printf("Message from server: %s\n", message);           //输出接收到的消息字符串
    
    }
    printf("stop receive thread\n");                           //输出停止接收消息线程的消息
}