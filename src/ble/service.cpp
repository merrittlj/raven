#include "service.hpp"

T* BLE::Service::Instance(T* cur)
{
    if (!theInstance) theInstance = cur;
    return theInstance;
}

virtual BLE::Service::~Service()
{
    delete theInstance;
}
