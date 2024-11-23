#include "service.hpp"

static T* BLE::Service::Instance()
{
    if (!theInstance) theInstance = new T();
    return theInstance;
}

virtual BLE::Service::~Service()
{
    delete theInstance;
}
