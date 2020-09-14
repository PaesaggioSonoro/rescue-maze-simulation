#include "UBus.hpp"

UBus::UBus()
{
}

void UBus::setBus(DrivableActor* Actor)
{
    this->Bus = Actor;
}

DrivableActor* UBus::getBus()
{
    return Bus;
}
