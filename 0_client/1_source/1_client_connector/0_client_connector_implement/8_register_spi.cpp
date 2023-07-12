#include "../0_client_connector.h"

void client_connector::register_spi(future_spi* spi)
{
    this->spi = spi;
}