#include "../0_client_connector.h"
#include <string.h>
void client_connector::stop_receive()
{
    stop_receive_thread.exchange(true);
    char stop_msg[5] = {0};
    strcpy(stop_msg, "stop");
    send_to_server(stop_msg, 5);
}