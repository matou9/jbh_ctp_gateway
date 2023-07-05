#include "../0_server_connector.h"
#include <string.h>
#include <unistd.h>

void server_connector::receive_client_message(int client_socket)
{
    while (stop_interact_threads[client_socket].load() == false)
    {
        //TODO将其写入队列
        char message[BUF_SIZE];
        int message_length;
        message_length = read(client_socket, message, BUF_SIZE);
        if(message_length == 0)
        {
            stop_interact_threads[client_socket].exchange(true);
            printf("client %d disconnected\n", client_socket);
            current_client_number.fetch_sub(1);
            printf("current client num: %d\n", current_client_number.load());
            break;
        }
        char *p_message = message; 
        p_message[message_length] = '\0';
        
        if (strcmp(p_message, "stop") == 0)
        {
            char bye_message[4] = {0};
            strcpy(bye_message, "bye");
            send_to_client(client_socket, bye_message, strlen(bye_message));//客户端申请断开连接时, 需要服务端发送一个消息, 以使得客户端read()函数不再阻塞
            return;
        }

    }


}