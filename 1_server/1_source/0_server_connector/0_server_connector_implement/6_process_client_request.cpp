#include "../0_server_connector.h"

void server_connector::process_client_request(char* p_message, int message_length)
{
    printf("process client request: %s\n", p_message);

}