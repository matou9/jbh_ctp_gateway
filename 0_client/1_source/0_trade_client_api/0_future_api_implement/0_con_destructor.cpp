#include "0_include/1_future_api.h"

future_api::future_api() : connector(nullptr)
{

}

future_api::~future_api()
{
    if (connector != nullptr)
    {
        connector->close_connection();
        delete connector;
        connector = nullptr;
    }
    
}
