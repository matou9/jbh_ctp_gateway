/*
 * 0_server_connector.h
 * 交易服务端tcp连接类声明
 * created by 唐尚涛
 */

#include "1_source/1_future_server/1_CTP_gateway/0_CTP_gateway.h"

#include <arpa/inet.h>
#include <string>
#include <thread>
#include <unordered_map>
#include <atomic>
#include <queue>
#include <mutex>
#include <utility>
#define BUF_SIZE 1024
class server_connector
{
private:
    int max_client_number;
    std::atomic<int> current_client_number;
    int server_socket;
    struct sockaddr_in server_address;
    

    std::thread* accept_thread;
    std::unordered_map<int, std::thread*> interact_threads;
    std::unordered_map<int, std::atomic<bool>> stop_interact_threads;

    //在main中创建、初始化和启动CTP_gateway和server_connector, 并且
    //以下的问题: 请求接收线程、请求队列、请求处理线程--全部在server_connector中实现(耦合问题?)
    //设计一个有锁队列, 用于存放客户端请求
    std::mutex client_request_queue_mutex;
    std::queue<std::pair<char*, int>> client_request_queue;//客户端请求buffer, 以及buffer长度
    //再创建一个线程, 取出客户端请求, 调用CTPGateway处理(存放一个CTPGateway的指针);
    CTP_gateway* p_trade_gateway; //需要在main函数中提前准备好CTP交易环境(连接、登录), 再传入server_connector中(通过初始化)
    std::thread* process_client_request_thread;
    //设计一个有锁队列, 用于存放CTPGateway的回报, (再创建一个线程)取出回报, 发送给客户端;


private:
    void error_handling(std::string message);
    void init(std::string port);
    void accept_clients();
    void receive_client_message(int client_socket);
    //将客户端请求写入队列
    void write_message_to_queue(char* message, int message_length);
    //从队列中取出客户端请求, 交给CTPGateway处理
    void read_message_from_queue();

    void send_to_client(int client_socket, char* message, int message_length);
    void stop_interact_with_client(int client_socket);
public:
    server_connector(std::string port, int max_client_number);
    ~server_connector();
    void run_server();
    
};