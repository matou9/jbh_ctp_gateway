#include "0_server_connector.h"

#include <string.h>

void server_connector::process_client_message(int clnt_sock, char* message, int str_len)
{
    message[str_len] = '\0';
    
    if (strcmp(message, "stop") == 0)
    {
        char bye_msg[4] = {0};
        strcpy(bye_msg, "bye");
        send_to_client(clnt_sock, bye_msg, strlen(bye_msg));
        return;
    }
    //具体实现处理message的逻辑
    // write(clnt_sock, message, str_len);
    printf("Message from client %d: %s\n", clnt_sock, message);
}