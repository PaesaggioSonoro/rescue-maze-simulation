#include "UBus.h"

UBus::UBus()
{
}

void UBus::SetBus(DrivableActor* Actor)
{
    this->Bus = Actor;
}

DrivableActor* UBus::GetBus()
{
    return Bus;
}
