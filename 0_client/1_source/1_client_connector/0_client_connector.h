/*
 * 0_client_connector.h
 * 客户端tcp连接类
 * created by 唐尚涛
 */

#ifndef CLIENT_CONNECTOR_H
#define CLIENT_CONNECTOR_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <thread>
#include <atomic>
#include <unistd.h>

/*
 * 定义交易接口api名称枚举变量, 添加至数据报的首地址, 用于区分不同的交易接口api
 */
typedef enum
{
    E_LIMIT_ENTRUST_INSERT,
    E_LIMIT_ORDER_CANCEL,

}api_type;

#define BUF_SIZE 1024
class client_connector
{
private:
    int sock;
    struct sockaddr_in serv_adr;

    std::atomic<bool> stop_receive_thread;
    std::thread* receive_thread;
private:
    void error_handling(std::string message);
    void init(std::string ip, std::string port);
    void connect_to_server();
    void receive_from_server();
public:
    void start_receive();
    void send_to_server(char* message, int len);

    void stop_receive();

public:
    client_connector(std::string ip, std::string port);
    ~client_connector();

};











#endif