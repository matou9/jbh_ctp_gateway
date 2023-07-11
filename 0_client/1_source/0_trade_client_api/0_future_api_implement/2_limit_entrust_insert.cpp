#include "0_include/1_future_api.h"
#include <string.h>

#define MEM_PADDING_SIZE 8
void future_api::limit_entrust_insert(future_limit_entrust *entrust)
{
    if (entrust == nullptr)
    {
        return;
    }
    
    char buf[BUF_SIZE];
    memset(buf, 0, BUF_SIZE);
    char* ptr = buf;
    ptr[0] = E_LIMIT_ENTRUST_INSERT;
    ptr += MEM_PADDING_SIZE;
    memcpy(ptr, entrust, sizeof(future_limit_entrust));
    
    connector->send_to_server(buf, sizeof(future_limit_entrust) + MEM_PADDING_SIZE);
    
}