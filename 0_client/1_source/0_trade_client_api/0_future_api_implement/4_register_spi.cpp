#include "0_include/1_future_api.h"

void future_api::register_spi(future_spi* spi)
{
    connector->register_spi(spi);
}