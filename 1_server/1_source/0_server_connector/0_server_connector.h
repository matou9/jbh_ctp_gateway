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
#include <condition_variable>
#include <stdint.h>


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

    CTP_gateway* p_trade_gateway; 

    
    std::mutex client_request_queue_mutex;
    std::condition_variable client_request_queue_condition_variable;
    uint32_t client_request_queue_max_size;
    std::queue<std::pair<char*, int>*> client_request_queue;
    std::thread* process_client_request_thread;


private:
    void error_handling(std::string message);
    void init(std::string port);
    void accept_clients();
    void receive_client_message(int client_socket);
    //将客户端请求写入队列
    void write_message_to_queue(char* message, int message_length);
    //从队列中取出客户端请求, 交给CTPGateway处理
    void read_message_from_queue();
    void process_client_request(char* p_message, int message_length);
    void send_to_client(int client_socket, char* message, int message_length);
    void stop_interact_with_client(int client_socket);
public:
    server_connector(std::string port, int max_client_number);
    ~server_connector();
    void run_server();
    void add_gateway(CTP_gateway* p_gateway);
    
};