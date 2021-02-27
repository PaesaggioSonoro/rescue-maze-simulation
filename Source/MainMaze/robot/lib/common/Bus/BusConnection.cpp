#include "BusConnection.hpp"

#if _EXECUTION_ENVIRONMENT == 0

DrivableActor* BusConnection::_Bus = nullptr;

void BusConnection::setBus(DrivableActor* Actor)
{
    _Bus = Actor;
}

DrivableActor* BusConnection::getBus()
{
    return _Bus;
}
#endif