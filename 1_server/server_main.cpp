#include "1_source/0_server_connector/0_server_connector.h"

int main()
{
    server_connector server("1234", 10);
    server.run_server();
    return 0;
}