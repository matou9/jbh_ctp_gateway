#include "0_server_connector.h"

#include <unistd.h>

void server_connector::interact_with_one_client(int clnt_sock)
{
    while (stop_interact_threads[clnt_sock].load() == false)
    {
        char message[BUF_SIZE];
        int str_len;
        str_len = read(clnt_sock, message, BUF_SIZE);
        if(str_len == 0)
        {
            stop_interact_threads[clnt_sock].exchange(true);
            break;
        }
        process_client_message(clnt_sock, message, str_len);
    }


}