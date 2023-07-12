#include "../0_client_connector.h"
#include "0_include/1_future_api.h"

// typedef enum
// {
//     // E_ON_TRADE_ERROR,
//     E_ON_ENTRUST_INSERTED,
//     E_ON_ORDER_STATUS_UPDATE,
//     E_ON_TRADE_UPDATE,
// }callback_type;

#define MEM_PADDING_SIZE 8

void client_connector::receive_from_server()
{
    while(true) 
    {
        char* p_message = new char[BUF_SIZE];
        int message_length;
        message_length = read(sock, p_message, BUF_SIZE-1);              //接收来自服务器端的消息
        if (message_length == -1 || message_length == 0)
        {
            printf("server disconnected by error\n");
            delete [] p_message;
            break;
        }
        if (message_length == 1 && p_message[0] == -1)
        {
            printf("server accepted disconnect request\n");
            delete [] p_message;
            break;
        }
        p_message[message_length]= '\0';                               
        // printf("Message from server: %s\n", p_message);           //输出接收到的消息字符串
        //一个成员变量, 取走这个消息, 根据开头的标识, 执行事件回调
        if (spi == nullptr)
        {
            printf("spi not registered\n");
            delete [] p_message;
            break;
        }
        char *move_pointer = p_message;
        callback_type type = (callback_type)(move_pointer[0]);
        move_pointer += MEM_PADDING_SIZE;
        if (type == E_ON_ENTRUST_INSERTED)
        {
            spi->on_entrust_inserted((future_limit_entrust*)move_pointer);
        }
        else if (type == E_ON_ORDER_STATUS_UPDATE)
        {
            spi->on_order_status_update((future_limit_order*)move_pointer);
        }
        else if (type == E_ON_TRADE_UPDATE)
        {
            spi->on_trade_update((future_limit_trade*)move_pointer);
        }
    }
    printf("stop receive thread\n");                           //输出停止接收消息线程的消息
}

// void write_to_file(char* message, int message_length)
// {
//         char *p_message = message;
//         callback_type type = (callback_type)(p_message[0]);
//         if (type == E_ON_CONNECTED)
//         {
//             printf("connected\n");
//         }
//         else if (type == E_ON_DISCONNECTED)
//         {
//             printf("disconnected\n");
//         }
//         else if (type == E_ON_ORDER_STATUS_UPDATE)
//         {
//             p_message += sizeof(callback_type);
//             FILE* fp = fopen("order_status_update.txt", "a");
//             fwrite(p_message, 1, message_length - sizeof(callback_type), fp);
//         }
//         else if (type == E_ON_TRADE_UPDATE)
//         {
//             p_message += sizeof(callback_type);
//             FILE* fp = fopen("trade_update.txt", "a");
//             fwrite(p_message, 1, message_length - sizeof(callback_type), fp);
//         }
//         else
//         {
//             printf("unknown message type\n");
//         }

// }