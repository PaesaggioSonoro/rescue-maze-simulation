// Fill out your copyright notice in the Description page of Project Settings.


#include "MLX90614.h"

MLX90614::MLX90614(uint8_t addr) {}

void MLX90614::begin(AActor* TMainCharacter)
{
	MainCharacter = TMainCharacter;
}

double MLX90614::read(void)
{
	FHitResult OutHit;

	FVector Start = MainCharacter->GetActorLocation();
	FVector ForwardVector = MainCharacter->GetActorForwardVector();

	FVector End = (Start + (ForwardVector * 1000.0f));

	FCollisionQueryParams CollisionParams;

	DrawDebugLine(MainCharacter->GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	bool isHit = MainCharacter->GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
	return 30;
	/*
	if (isHit)
	{
		if (OutHit.bBlockingHit)
		{
			if (GEngine)
			{
				auto hitted = OutHit.Actor;
				//bool hot = hitted->Hot;
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"),
					*OutHit.GetActor()->GetName()));

				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Distance: %f"),
					OutHit.Distance));
			}
		} else
		{
			return 30;
		}
	} else
	{
		return 30;
	}*/

}

