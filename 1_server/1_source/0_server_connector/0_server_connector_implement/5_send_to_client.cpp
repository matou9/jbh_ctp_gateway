#include "0_server_connector.h"

#include <unistd.h>

void server_connector::send_to_client(int clnt_sock, char* message, int str_len)
{
    write(clnt_sock, message, str_len);
}
