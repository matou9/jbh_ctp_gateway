#include "0_include/1_future_api.h"
#include <string.h>

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
    


}