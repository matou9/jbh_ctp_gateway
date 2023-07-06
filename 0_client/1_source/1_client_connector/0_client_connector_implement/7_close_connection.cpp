#include "../0_client_connector.h"
#include <unistd.h>
void client_connector::close_connection()
{
    char close_message = -1;
    write(sock, &close_message, 1); // 向服务器端发送关闭连接消息(1字节)
    if (receive_thread != nullptr) 
    { // 等待接收线程结束
        receive_thread->join();
        delete receive_thread; // 释放线程对象的内存

    }
    if (sock != -1) 
    { // 关闭套接字
        close(sock);
        sock = -1;
    }
}