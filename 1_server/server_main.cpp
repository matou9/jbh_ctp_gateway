#include "1_source/0_server_connector/0_server_connector.h"
#include <string.h>
int main(int argc, char** argv)
{
    // if (argc != 2)
    // {
    //     printf("input port\n");
    //     exit(1);
    // }
    // std::string port = argv[1];
    std::string port = "1234";
    server_connector server(port, 10);
    server.run_server();
    return 0;
}