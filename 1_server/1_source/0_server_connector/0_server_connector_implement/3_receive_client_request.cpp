#include "../0_server_connector.h"
#include <string.h>
#include <unistd.h>
#include <string>
void server_connector::receive_client_request(int client_socket)
{
    while (stop_interact_threads[client_socket].load() == false)
    {
        //TODO将其写入队列
        char* p_message = new char[BUF_SIZE];
        int message_length;
        message_length = read(client_socket, p_message, BUF_SIZE);
        if (message_length == -1)
        {
            printf("client %d disconnected by error\n", client_socket);
            delete [] p_message;
            break;
        }
        if(message_length == 0)
        {
            delete [] p_message;
            stop_interact_threads[client_socket].exchange(true);
            printf("client %d disconnected\n", client_socket);
            current_client_number.fetch_sub(1);
            printf("current client num: %d\n", current_client_number.load());
            break;
        }
        
        if (p_message[0] == -1)
        {
            printf("receive client disconnect request\n");
            char close_message = -1;
            write(client_socket, &close_message, 1);//客户端申请断开连接时, 需要服务端发送一个消息, 以使得客户端read()函数不再阻塞
        }
        else
        {
            printf("receive client request\n");
            

            write_client_request_to_queue(client_socket, p_message, message_length);
        }
    }


}