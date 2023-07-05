#include "../0_server_connector.h"

#include <unistd.h>

void server_connector::send_to_client(int client_socket, char* message, int message_length)
{
    write(client_socket, message, message_length);
}
