#include "../0_client_connector.h"

void client_connector::start_receive()
{
    receive_thread = new std::thread(&client_connector::receive_from_server, this);
}