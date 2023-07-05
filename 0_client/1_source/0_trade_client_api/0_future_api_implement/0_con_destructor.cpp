#include "0_include/1_future_api.h"

future_api::future_api() : connector(nullptr), is_connected(false)
{

}

future_api::~future_api()
{
    if (connector != nullptr)
    {
        connector->stop_receive();
        delete connector;
        connector = nullptr;
    }
    
}
